#include "../includes/space.h"

void	free_item(t_item *item)
{
	if (!item)
		return ;
	if (item->name)
		free(item->name);
	if (item->description)
		free(item->description);
	if (item->type)
		free(item->type);
	free(item);
}

void	free_inventory(t_inventory *inv)
{
	t_item	*tmp;

	if (!inv)
		return;
	if (inv->item)
	{
		while (inv->item)
		{
			tmp = inv->item;
			inv->item = inv->item->next;
			free_item(tmp);
		}
	}
	free(inv);
}

void	free_character(t_char *character)
{
	if (character->name)
		free(character->name);
	if (character->inventory)
		free_inventory(character->inventory);
	free(character);
}

void	free_char_array(char **arr)
{
	int	i = 0;

	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_location(t_location *location)
{
	if (!location)
		return ;
	if (location->name)
		free(location->name);
	if (location->description)
		free(location->description);
	free_char_array(location->options);
	free_char_array(location->enemies);
	free(location);
}

void	free_map(t_data *data)
{
	t_location	*location;
	t_location	*tmp;

	if (data->map)
	{
		location = data->map;
		while (location)
		{
			tmp = location;
			location = location->next;
			free_location(tmp);
		}
	}
}

void	free_data(t_data *data)
{
	t_char	*tmp;

	free_character(data->char_main);
	while (data->enemies)
	{
		tmp = data->enemies;
		data->enemies = data->enemies->next;
		free_character(tmp);
	}
	free_inventory(data->inventory);
	free_map(data);
}
