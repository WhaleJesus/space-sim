#include "../includes/space.h"

int	battle(t_char *main, t_char *enemy)
{
	int		option;
	int		ret;

	if (!main || !enemy)
		return (-1);
	clear_console();
	while (main->hp > 0 && enemy->hp > 0)
	{
		printf("%s\nhp: %i\n\n%s\nhp: %i\n\n", enemy->name, enemy->hp, main->name, main->hp);
		option = -1;
		while (option < 1)
		{
			option = get_input_int("Options:\n1. Attack\n");
			if (option < 1)
				printf("wrong input.\n");
		}
		if (option == 1)
		{
			clear_console();
			printf("%s attacks %s for %i damage!\n", main->name, enemy->name, main->attack);
			enemy->hp -= main->attack;
			if (enemy->hp <= 0)
			{
				printf("%s was defeated!\n", enemy->name);
				get_input_int("press enter to continue..");
				break ;
			}
		}
		main->hp -= enemy->attack;
		printf("%s attacks %s for %i damage!\n", enemy->name, main->name, enemy->attack);
	}
	free_char(enemy);
	if (main->hp <= 0)
		ret = 0;
	else
		ret = 1;
	return (ret);
}
