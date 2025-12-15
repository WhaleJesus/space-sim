#include "../includes/space.h"

t_char	*init_char(char *name, int hp, int attack)
{
	t_char	*character = malloc(sizeof(t_char));
	if (!character)
		return (NULL);
	character->name = (char *)malloc(strlen(name) + 1);
	if (!character->name)
		return (NULL);
	strcpy(character->name, name);
	character->hp = hp;
	character->attack = attack;
	character->prev = NULL;
	character->next = NULL;
	return (character);
}

void	init_data_enemies(t_data *data)
{
	data->enemies = init_char("goblin", 25, 3);
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

void	init_data(t_data *data)
{
	data->char_main = NULL;
	data->enemies = NULL;
	data->map = NULL;
	data->map_width = 2;
	data->map_height = 3;
	data->exit = 0;
	init_data_enemies(data);
	init_data_locations(data);
	//print_locations(data->map);
}
