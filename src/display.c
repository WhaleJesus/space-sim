#include "../includes/space.h"

void	display_location(t_data *data)
{
	t_location	*location;
	int			option;
	int			i;

	if (!data)
		return ;
	location = data->current_location;
	option = -1;
	while (option <= 0 || option > i)
	{
		//clear_console();
		printf("location: %s | x: %i y: %i\n\n%s\n\noptions:\n", location->name, location->x, location->y, location->description);
		i = 0;
		while (location->options[i])
		{
			printf("%i: %s\n", i + 1, location->options[i]);
			i++;
		}
		option = get_input_int("");
		if (option <= 0 || option > i)
			get_input("wrong input, press enter to continue...\n");
		else 
			handle_location_option(data, location, option - 1);
	}
}
