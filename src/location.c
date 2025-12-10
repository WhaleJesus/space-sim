#include "../includes/space.h"

void	handle_location_move(t_data *data, t_location *location)
{
	int	input = -1;

	if (location->north)
		printf("1. North: %s\n", location->north->name);
	if (location->east)
		printf("2. East: %s\n", location->east->name);
	if (location->south)
		printf("3. South: %s\n", location->south->name);
	if (location->west)
		printf("4. West: %s\n", location->west->name);
	while (input > -2)
	{
		input = get_input_int("Where do you want to go?\n");
		if (input == 1 && location->north != NULL)
		{
			data->current_location = location->north;
			break ;
		}
		else if (input == 2 && location->east != NULL)
		{
			data->current_location = location->east;
			break ;
		}
		else if (input == 3 && location->south != NULL)
		{
			data->current_location = location->south;
			break ;
		}
		else if (input == 4 && location->west != NULL)
		{
			data->current_location = location->west;
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
