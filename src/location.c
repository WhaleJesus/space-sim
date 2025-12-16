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

void	handle_location_option(t_data *data, t_location *location, int i)
{
	char	*option = location->options[i];
	int		r;

	if (!strcmp(option, "move"))
		handle_location_move(data, location);
	if (!strcmp(option, "inventory"))
		display_inventory(data->char_main, data->char_main->inventory);
	if (!strcmp(option, "battle"))
	{
		r = rand_range(0, char_arr_len(location->enemies) - 1);
		printf("debug: r: %i len: %i\n", r, char_arr_len(location->enemies));
		r = battle(data->char_main, get_enemy(data, data->enemies, location->enemies[r]));
		if (r == 0)
		{
			get_input_int("you died.\npress enter to continue");
			data->exit = 1;
		}
		else 
			printf("debug: battle: %i\n", r);
	}
	if (!strcmp(option, "exit"))
		data->exit = 1;
}
