#include "../includes/space.h"

void	handle_location_move(t_data *data, t_location *location)
{
	int		input = -1;
	int		i = 0;
	char	*directions[4];
	char	*direction;

	if (location->y > 0)
	{
		printf("%i. North: %s\n", i + 1, get_map_location(data->map, location->x, location->y - 1)->name);
		directions[i] = "north";
		i++;
	}
	if (location->x < data->map_width - 1)
	{
		printf("%i. East: %s\n", i + 1, get_map_location(data->map, location->x + 1, location->y)->name);
		directions[i] = "east";
		i++;
	}
	if (location->y < data->map_height - 1)
	{
		printf("%i. South: %s\n", i + 1, get_map_location(data->map, location->x, location->y + 1)->name);
		directions[i] = "south";
		i++;
	}
	if (location->x > 0)
	{
		printf("%i. West: %s\n", i + 1, get_map_location(data->map, location->x - 1, location->y)->name);
		directions[i] = "west";
		i++;
	}
	printf("%i. back\n", i + 1);
	directions[i] = "back";
	while (input > -2)
	{
		input = get_input_int("Where do you want to go?\n") - 1;
		if (input >= 0 && input <= i)
		{
			direction = directions[input];
			if (!strcmp(direction, "north"))
			{
				data->current_location = get_map_location(data->map, location->x, location->y -1);
				break ;
			}
			if (!strcmp(direction, "east"))
			{
				data->current_location = get_map_location(data->map, location->x + 1, location->y);
				break ;
			}
			if (!strcmp(direction, "south"))
			{
				data->current_location = get_map_location(data->map, location->x, location->y + 1);
				break ;
			}
			if (!strcmp(direction, "west"))
			{
				data->current_location = get_map_location(data->map, location->x - 1, location->y);;
				break ;
			}
			if (!strcmp(direction, "back"))
				break ;
		}
		else 
			printf("Can't go that way.\n");
	}
}

void	handle_location_option(t_data *data, t_location *location, t_option **options, int i)
{
	t_option	*option = options[i];
	int			r;

	if (!strcmp(option->text, "move"))
		handle_location_move(data, location);
	else if (!strcmp(option->text, "character"))
		display_character(data->char_main);
	else if (!strcmp(option->text, "inventory"))
		display_inventory(data, data->char_main, data->char_main->inventory, 1, 0);
	else if (!strcmp(option->text, "battle"))
	{
		r = rand_range(0, ptr_arr_len((void **)location->enemies) - 1);
		printf("debug: r: %i len: %i\n", r, ptr_arr_len((void **)location->enemies));
		r = battle(data, data->char_main, get_enemy(data, data->enemies, location->enemies[r]));
		if (r == 0)
		{
			get_input_int("you died.\npress enter to continue");
			data->exit = 1;
		}
	}
	else if (!strcmp(option->text, "talk"))
	{
		int		i = 0;
		int		len;
		int		input = -1;

		len = ptr_arr_len((void **)location->characters);
		while (i < len)
		{
			printf("%i. %s\n", i + 1, location->characters[i]->name);
			i++;
		}
		while (input < 1 || input > i)
		{
			input = get_input_int("");
			if (input < 1 || input > i)
				printf("wrong input\n");
			else
			{
				i--;
				display_dialogue(data, location->characters[i], location->characters[i]->dialogue);
				break ;
			}
		}
	}
	else if (!strcmp(option->text, "gather resources"))
		location_gather_resources(data, data->char_main, location);
	if (!strcmp(option->text, "exit"))
		data->exit = 1;
}

int	location_add_character(t_location *location, t_char *c)
{
	t_char	**characters;
	int		i;
	int		len;

	if (!location->characters)
		len = 1;
	else
		len = ptr_arr_len((void **)location->characters) + 1;
	characters = malloc(sizeof(t_char *) * (len + 1));
	if (!characters)
		return (0);
	i = 0;
	if (location->characters)
	{
		while (i < len)
		{
			characters[i] = location->characters[i];
			i++;
		}
	}
	characters[i] = c;
	characters[++i] = NULL;
	free(location->characters);
	location->characters = characters;
	return (1);
}

int	location_gather_resources(t_data *data, t_char *c, t_location *location)
{
	int		rand;
	int		times;
	t_item	*item;

	// time_forward() TODO
	if (!data || !c || !location)
		return (0);
	times = rand_range(1, 5);
	for (int i = 0; i < times; i++)
	{
		rand = rand_range(1, location->resources->size);
		item = copy_item_by_pos(location->resources->item, rand);
		if (item)
			inventory_add_item(c->inventory, item, 1);
	}
	get_input_int("press enter to continue");
	return (1);
}

int	location_build(t_data *data, t_location *location)
{
	
}