#include "../includes/space.h"

int	init_char_main(t_data *data)
{
	t_char	*char_main;

	char_main = malloc(sizeof(t_char));
	if (!char_main)
		return (0);
	char_main->next = NULL;
	char_main->prev = NULL;
	char_main->hp = 100;
	char_main->attack = 10;
	char_main->inventory = init_inventory(data->inventory_base_size);
	char_main->name = "";
	while (strlen(char_main->name) == 0)
	{
		char *temp = get_input("Enter name");
		if (strlen(temp) == 0)
		{
			free(temp);
			printf("bad input.\n");
		}
		else
			char_main->name = temp;
	}
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
	srand(time(NULL));   // seed once
	while (!data.exit)
		display_location(&data);
//	battle(data.char_main, get_enemy(data.enemies, "Goblin"));
	free_data(&data);
	return (0);
}
