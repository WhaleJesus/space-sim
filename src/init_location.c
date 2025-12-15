#include "../includes/space.h"

t_location	*init_location_base(char *name, char *description, int x, int y)
{
	t_location	*location;

	location = malloc(sizeof(t_location) + 1);
	if (!location)
		return (NULL);
	location->name = ft_strdup(name);
	location->description = ft_strdup(description);
	location->options = (char **)malloc(sizeof(char *) * 3);
	if (!location->options)
	{
		free_location(location);
		return (NULL);
	}
	location->options[0] = ft_strdup("move");
	location->options[1] = ft_strdup("exit");
	location->options[2] = NULL;
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
	char		**options;

	location = init_location_base("plains", "lots of grass", x, y);
	if (!location)
		return (NULL);
	options = add_option(location->options, "battle");
	if (!options)
	{
		free_location(location);
		return (NULL);
	}
	free_char_array(location->options);
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
