#include "../includes/space.h"

t_char	*init_goblin(t_data *data)
{
	t_char	*enemy;

	enemy = init_char(data, "goblin", 25, "knife");
	init_character_stats(enemy, 2, 3, 3, 1, 2, 3);
	return (enemy);
}
