#include "../includes/space.h"

t_inventory	*copy_inventory(t_data *data, t_inventory *src)
{
	t_inventory	*inv;
	t_item		*head;
	t_item		*tmp;

	if (!src)
		return (NULL);
	inv = init_inventory(src->maxSize);
	head = src->item;
	while (head)
	{
		tmp = get_item_by_name(data, data->inventory->item, head->name);
		inventory_add_item(inv, tmp);
		head = head->next;
	}
	return (inv);
}

t_char	*copy_enemy(t_data *data, t_char *enemy_tmp)
{
	t_char	*enemy = malloc(sizeof(t_char));
	t_item	*weapon;

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
	enemy->hp_max = enemy_tmp->hp_max;
	enemy->intelligence = enemy_tmp->intelligence;
	enemy->strength = enemy_tmp->strength;
	enemy->perception = enemy_tmp->perception;
	enemy->charisma = enemy_tmp->charisma;
	enemy->stealth = enemy_tmp->stealth;
	enemy->speed = enemy_tmp->speed;
	enemy->dead = 0;
	enemy->inventory = copy_inventory(data, enemy_tmp->inventory);
	if (!enemy->inventory)
	{
		free_character(enemy);
		return (NULL);
	}
	enemy->weapon = NULL;
	weapon = get_item_by_pos(enemy->inventory->item, get_item_pos_by_name(enemy->inventory->item, enemy_tmp->weapon->name));
	equip_weapon_from_inv(enemy, enemy->inventory, weapon->id);
	enemy->prev = NULL;
	enemy->next = NULL;
	return (enemy);
}

t_char	*get_enemy(t_data *data, t_char *enemies, char *name)
{
	t_char *head;
	t_char *ret;

	ret = NULL;
	head = enemies;
	while (head != NULL)
	{
		if (strcmp(head->name, name) == 0)
		{
			ret = copy_enemy(data, head);
			break ;
		}
		head = head->next;
	}
	return (ret);
}

t_item	*get_item_by_pos(t_item *src, int pos)
{
	int		i = 1;
	t_item	*head;

	if (!src || pos < 1)
		return (NULL);
	head = src;
	while (head && i != pos)
	{
		head = head->next;
		i++;
	}
	if (i != pos)
		return (NULL);
	return (head);
}

int	get_item_pos_by_name(t_item *src, char *name)
{
	t_item	*head;
	int		ret;

	if (!src)
		return (0);
	head = src;
	ret = 1;
	while (head)
	{
		if (!strcmp(head->name, name))
			return (ret);
		ret++;
		head = head->next;
	}
	return (0);
}

t_item	*get_item_by_name(t_data *data, t_item *src, char *name)
{
	t_item	*dst;
	t_item	*head;

	if (!src || strlen(name) < 1)
		return (NULL);
	dst = NULL;
	head = src;
	while (head)
	{
		if (!strcmp(head->name, name))
		{
			dst = init_item(data, head->name, head->description, head->type, head->stat, head->c_stat, head->stat_mult, head->can_drop);
			break ;
		}
		head = head->next;
	}
	return (dst);
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
