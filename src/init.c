#include "../includes/space.h"

t_item	*init_item(char *name, char *description, char *type, int stat)
{
	t_item	*item;

	item = malloc(sizeof(t_item) + 1);
	if (!item)
		return (NULL);
	item->name = ft_strdup(name);
	item->description = ft_strdup(description);
	item->type = ft_strdup(type);
	item->stat = stat;
	if (!item->name || !item->description || !item->type)
	{
		free_item(item);
		return (NULL);
	}
	item->prev = NULL;
	item->next = NULL;
	return (item);
}

t_inventory	*init_inventory(int maxSize)
{
	t_inventory	*inv;

	inv = malloc(sizeof(t_inventory) + 1);
	if (!inv)
		return (NULL);
	inv->item = NULL;
	inv->size = 0;
	inv->maxSize = maxSize;
	return (inv);
}

t_char	*init_char(t_data *data, char *name, int hp, int attack)
{
	t_char	*character = malloc(sizeof(t_char));
	if (!character)
		return (NULL);
	character->name = (char *)malloc(strlen(name) + 1);
	if (!character->name)
	{
		free_character(character);
		return (NULL);
	}
	strcpy(character->name, name);
	character->hp = hp;
	character->attack = attack;
	character->inventory = init_inventory(data->inventory_base_size);
	if (!character->inventory)
	{
		free_character(character);
		return (NULL);
	}
	character->prev = NULL;
	character->next = NULL;
	return (character);
}

void	init_data_enemies(t_data *data)
{
	data->enemies = init_char(data, "goblin", 25, 3);
}

void	print_locations(t_location *location)
{
	while (location)
	{
		printf("%s x: %i y: %i\n", location->name, location->x, location->y);
		location = location->next;
	}
}

void	init_data_locations(t_data *data)
{
	int			y = 0;
	int			x;
	t_location	*location;

	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			location = init_location_plains(x, y);
			if (!location)
			{
				free_map(data);
				data->exit = 1;
				return ;
			}
			location->prev = NULL;
			location->next = NULL;
			if (!data->map)
				data->map = location;
			else 
			{
				location->prev = data->current_location;
				location->prev->next = location;
			}
			data->current_location = location;
			x++;
		}
		y++;
	}
}

void	init_data_items(t_data *data)
{
	t_item	*item;

	data->inventory = init_inventory(-1);
	item = init_item("knife", "a small rusty blade", "weapon", 3);
	inventory_add_item(data->inventory, item);
	item = init_item("apple", "should keep the doctor away", "food", 5);
	inventory_add_item(data->inventory, item);
}

void	init_data(t_data *data)
{
	data->char_main = NULL;
	data->enemies = NULL;
	data->map = NULL;
	data->map_width = 2;
	data->map_height = 3;
	data->inventory_base_size = 10;
	data->exit = 0;
	init_data_enemies(data);
	init_data_locations(data);
	//print_locations(data->map);
}
