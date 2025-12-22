#include "../includes/space.h"

t_location	*init_location_base(char *name, char *description, int x, int y)
{
	t_location	*location;

	location = malloc(sizeof(t_location) + 1);
	if (!location)
		return (NULL);
	location->name = ft_strdup(name);
	location->description = ft_strdup(description);
	location->options = malloc(sizeof(t_option *) * 5);
	if (!location->options)
	{
		free_location(location);
		return (NULL);
	}
	location->options[0] = init_option("move", 0, 0, STAT_NONE, 0);
	location->options[1] = init_option("character", 0, 0, STAT_NONE, 0);
	location->options[2] = init_option("inventory", 0, 0, STAT_NONE, 0);
	location->options[3] = init_option("exit", 0, 0, STAT_NONE, 0);
	location->options[4] = NULL;
	location->enemies = NULL;
	location->characters = NULL;
	location->x = x;
	location->y = y;
	if (!location->name || !location->description || !location->options[0] || !location->options[1])
	{
		free_location(location);
		return (NULL);
	}
	return (location);
}

t_location	*init_location_plains(int x, int y)
{
	t_location	*location;
	t_option	**options;

	location = init_location_base("plains", "lots of grass", x, y);
	if (!location)
		return (NULL);
	options = add_option(location->options, "battle", 0, 0, STAT_NONE, 0);
	if (!options)
	{
		free_location(location);
		return (NULL);
	}
	free_option_array(location->options);
	location->options = options;
	location->enemies = (char **)malloc(sizeof(char *) * 2);
	if (!location->enemies)
	{
		free_location(location);
		return (NULL);
	}
	location->enemies[0] = ft_strdup("goblin");;
	location->enemies[1] = NULL;
	return (location);
}
