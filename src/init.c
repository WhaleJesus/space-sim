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
	data->enemies = init_char("Goblin", 25, 3);
}

t_char	*copy_enemy(t_char *enemy_tmp)
{
	t_char	*enemy = malloc(sizeof(t_char));
	if (!enemy)
		return (NULL);
	enemy->name = malloc((sizeof(char) * strlen(enemy_tmp->name)) + 1);
	if (!enemy->name)
	{
		free(enemy);
		return (NULL);
	}
	strcpy(enemy->name, enemy_tmp->name);
	enemy->name[strlen(enemy->name)] = '\0';
	enemy->hp = enemy_tmp->hp;
	enemy->attack = enemy_tmp->attack;
	enemy->prev = NULL;
	enemy->next = NULL;
	return (enemy);
}

t_char	*get_enemy(t_char *enemies, char *name)
{
	t_char *head;
	t_char *ret;

	ret = NULL;
	head = enemies;
	while (head != NULL)
	{
		if (strcmp(head->name, name) == 0)
		{
			ret = copy_enemy(head);
			break ;
		}
		head = head->next;
	}
	return (ret);
}

t_location	*get_map_location(t_data *data, int x, int y)
{
	t_location	*location;

	location = data->map;
	while (location->y < y)
		location = location->south;
	while (location->x < x)
		location = location->east;
	return (location);
}

void	init_data_locations(t_data *data)
{
	int			y = 0;
	int			x;
	FILE		*fd;
	t_location	*location;

	fd = fopen("files/map.txt", "r");
	if (!fd)
	{
		data->exit = 1;
		return ;
	}
	while (y < 3)
	{
		x = 0;
		while (x < 2)
		{
			location = malloc(sizeof(t_location) + 1);
			if (!location)
			{
				free(location);
				free_map(data);
				return ;
			}
			read_location(location, fd);
			location->x = x;
			location->y = y;
			location->north = NULL;
			location->east = NULL;
			location->south = NULL;
			location->west = NULL;
			data->current_location = location;
			if (!data->map)
				data->map = location;
			else 
			{
				if (y > 0)
				{
					location->north = get_map_location(data, x, y - 1);
					location->north->south = location;
				}
				if (x > 0)
				{
					location->west = get_map_location(data, x - 1, y);
					location->west->east = location;
				}
			}
			x++;
		}
		y++;
	}
	fclose(fd);
}

void	init_data(t_data *data)
{
	data->char_main = NULL;
	data->enemies = NULL;
	data->map = NULL;
	data->exit = 0;
	init_data_enemies(data);
	init_data_locations(data);
}
