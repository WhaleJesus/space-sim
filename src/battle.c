#include "../includes/space.h"

void	attack(t_char *main, t_char *enemy)
{
	int	attack;
	
	attack = item_stat(main, main->weapon);
	printf("%s attacks\n", main->name);
	character_take_damage(enemy, attack);
}

void	enemy_turn(t_char *main, t_char *enemy)
{
	if (enemy->dead || main->dead)
		return ;
	attack(enemy, main);
}

void	player_turn(t_char *main, t_char *enemy)
{
	int		option;

	if (enemy->dead || main->dead)
		return ;
	if (DEBUG)
		printf("DEBUG: P %i E %i\n", main->speed, enemy->speed);
	printf("%s\nhp: %i/%i\n\n%s\nhp: %i/%i\n\n", enemy->name, enemy->hp, enemy->hp_max, main->name, main->hp, main->hp_max);
	printf("Options:\n1. Attack\n2. Inventory\n");
	option = -1;
	while (option < 1)
	{
		option = get_input_int("");
		if (option < 1 || option > 2)
		{
			option = -1;
			printf("wrong input.\n");
		}
	}
	if (!DEBUG)
		clear_console();
	if (option == 1)
		attack(main, enemy);
	else if (option == 2)
		display_inventory(main, main->inventory);

}

int	battle(t_char *main, t_char *enemy)
{
	int		ret;

	if (!main)
		return (-1);
	if (!enemy)
		return (-2);
	if (!DEBUG)
	clear_console();
	while (!main->dead && !enemy->dead)
	{
		if (main->speed > enemy->speed)
		{
			player_turn(main, enemy);
			enemy_turn(main, enemy);
		}
		else if (main->speed < enemy->speed)
		{
			enemy_turn(main, enemy);
			player_turn(main, enemy);
		}
		else 
		{
			int	diceRoll = rand_range(0, 1);
			if (diceRoll == 0)
			{
				player_turn(main, enemy);
				enemy_turn(main, enemy);
			}
			else 
			{
				enemy_turn(main, enemy);
				player_turn(main, enemy);
			}
		}
		if (enemy->dead)
		{
			character_add_xp(main, enemy->xp_on_death, 1);
			get_input_int("press enter to continue..");
		}
	}
	if (!DEBUG)
		clear_console();
	free_character(enemy);
	if (main->dead)
		ret = 0;
	else
		ret = 1;
	return (ret);
}
