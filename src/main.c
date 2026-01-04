#include "../includes/space.h"

int	init_char_main(t_data *data)
{
	t_char	*char_main;
	char	*name;

	name = "";
	while (strlen(name) == 0)
	{
		char *temp = get_input("Enter name");
		if (strlen(temp) == 0)
		{
			free(temp);
			printf("bad input.\n");
		}
		else
			name = temp;
	}
	char_main = init_char(data, name, 100, "knife");
	char_main->speed = 10;
	free(name);
	if (!char_main)
		return (0);
	inventory_add_item(char_main->inventory, get_item_by_name(data->inventory->item, "apple"), 0);
	data->char_main = char_main;
	return (1);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data	data;

	init_data(&data);
	location_add_character(get_map_location(data.map, 1, 2), init_npc_basic(&data));
	init_char_main(&data);
	print_inventory(data.inventory);
	print_inventory(data.char_main->inventory);
	srand(time(NULL));   // seed once
	while (!data.exit)
		display_location(&data);
	free_data(&data);
	return (0);
}
