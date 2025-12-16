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
	free(name);
	if (!char_main)
		return (0);
	// debug
	for (int i = 0; i < 23; i++)
	{
		int	j;
		t_item	*tmp = get_item_by_name(data->inventory->item, "knife");
		j = inventory_add_item(char_main->inventory, tmp);
		if (!j)
			free_item(tmp);
	}
	// debug
	data->char_main = char_main;
	return (1);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data	data;

	init_data(&data);
	init_char_main(&data);
	print_inventory(data.char_main->inventory);
	print_inventory(data.enemies->inventory);
	srand(time(NULL));   // seed once
	while (!data.exit)
		display_location(&data);
//	battle(data.char_main, get_enemy(data.enemies, "Goblin"));
	free_data(&data);
	return (0);
}
