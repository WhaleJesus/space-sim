#include "../includes/space.h"

void	handle_location_move(t_data *data, t_location *location)
{
	int		input = -1;
	int		i = 0;
	char	*directions[4];
	char	*direction;

	if (location->north)
	{
		printf("%i. North: %s\n", i + 1, location->north->name);
		directions[i] = "north";
		i++;
	}
	if (location->east)
	{
		printf("%i. East: %s\n", i + 1, location->east->name);
		directions[i] = "east";
		i++;
	}
	if (location->south)
	{
		printf("%i. South: %s\n", i + 1, location->south->name);
		directions[i] = "south";
		i++;
	}
	if (location->west)
	{
		printf("%i. West: %s\n", i + 1, location->west->name);
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
				data->current_location = location->north;
				break ;
			}
			if (!strcmp(direction, "east"))
			{
				data->current_location = location->east;
				break ;
			}
			if (!strcmp(direction, "south"))
			{
				data->current_location = location->south;
				break ;
			}
			if (!strcmp(direction, "west"))
			{
				data->current_location = location->west;
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

	if (!strcmp(option, "move"))
		handle_location_move(data, location);
	if (!strcmp(option, "exit"))
		data->exit = 1;
}
