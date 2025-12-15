#include "../includes/space.h"

void	attack(t_char *main, t_char *enemy)
{
	int	hp;
	int	attack;

	hp = enemy->hp;
	attack = main->attack;
	if (hp < attack)
		attack = hp;
	hp -= attack;
	printf("%s attacks %s for %i damage!\n", main->name, enemy->name, attack);
	enemy->hp = hp;
}

int	battle(t_char *main, t_char *enemy)
{
	int		option;
	int		ret;

	if (!main)
		return (-1);
	if (!enemy)
		return (-2);
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
			attack(main, enemy);
			if (enemy->hp <= 0)
			{
				printf("%s was defeated!\n", enemy->name);
				get_input_int("press enter to continue..");
				break ;
			}
		}
		attack(enemy, main);
	}
	free_char(enemy);
	if (main->hp <= 0)
		ret = 0;
	else
		ret = 1;
	return (ret);
}
