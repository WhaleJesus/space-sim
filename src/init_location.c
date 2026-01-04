#include "../includes/space.h"

t_location	*init_location_base(t_data *data, char *name, char *description, int x, int y)
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
	location->buildings = NULL;
	location->resources = init_inventory(data->inventory_base_size);
	location->can_build = 0;
	location->x = x;
	location->y = y;
	if (!location->name || !location->description || !location->options[0] || !location->options[1])
	{
		free_location(location);
		return (NULL);
	}
	return (location);
}

t_location	*init_location_plains(t_data *data, int x, int y)
{
	t_location	*location;

	location = init_location_base(data, "plains", "lots of grass", x, y);
	if (!location)
		return (NULL);
	location->options = add_option(location->options, "gather resources", 0, 0, STAT_NONE, 0);
	location->options = add_option(location->options, "battle", 0, 0, STAT_NONE, 0);
	if (!location->options)
	{
		free_location(location);
		return (NULL);
	}
	inventory_add_item(location->resources, get_item_by_name(data->inventory->item, "wood"), 0);
	location->enemies = (char **)malloc(sizeof(char *) * 2);
	if (!location->enemies)
	{
		free_location(location);
		return (NULL);
	}
	location->enemies[0] = ft_strdup("goblin");
	location->enemies[1] = NULL;
	location->can_build = 1;
	return (location);
}