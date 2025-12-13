#include "../includes/space.h"

t_char	*copy_enemy(t_char *enemy_tmp)
{
	t_char	*enemy = malloc(sizeof(t_char));
	if (!enemy)
		return (NULL);
	enemy->name = malloc((sizeof(char) * strlen(enemy_tmp->name)) + 1);
	if (!enemy->name)
	{
		free(enemy);
		return (NULL);
	}
	strcpy(enemy->name, enemy_tmp->name);
	enemy->name[strlen(enemy->name)] = '\0';
	enemy->hp = enemy_tmp->hp;
	enemy->attack = enemy_tmp->attack;
	enemy->prev = NULL;
	enemy->next = NULL;
	return (enemy);
}

t_char	*get_enemy(t_char *enemies, char *name)
{
	t_char *head;
	t_char *ret;

	ret = NULL;
	head = enemies;
	while (head != NULL)
	{
		if (strcmp(head->name, name) == 0)
		{
			ret = copy_enemy(head);
			break ;
		}
		head = head->next;
	}
	return (ret);
}

t_location	*get_map_location(t_location *map, int x, int y)
{
	t_location	*location;

	//printf("x %i y %i\n", x, y);
	if (!map || x < 0 || y < 0)
		return (NULL);
	location = map;
	while (location->prev)
		location = location->prev;
	while ((location->next) && ((location->x != x) || (location->y != y)))
		location = location->next;
	//printf("%s x: %i y: %i\n", location->name, location->x, location->y);
	if (location->x != x || location->y != y)
		return (NULL);
	return (location);
}
