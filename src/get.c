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
		tmp = get_item_by_name(data->inventory->item, head->name);
		inventory_add_item(inv, tmp);
		head = head->next;
	}
	return (inv);
}

t_option	*copy_option(t_option *src)
{
	t_option	*option;

	option = init_option(src->text, src->skill_check, src->req, src->stat, src->xp);
	if (!option)
		return (NULL);
	option->next = src->next;
	option->fail = src->fail;
	return (option);
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
	enemy->xp = enemy_tmp->xp;
	enemy->xp_to_next_lvl = enemy_tmp->xp_to_next_lvl;
	enemy->xp_on_death = enemy_tmp->xp_on_death;
	enemy->skill_points = enemy_tmp->skill_points;
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

t_char	*get_char_by_pos(t_char *c, int pos)
{
	int		i;
	t_char	*head;

	if (!c || pos < 1)
		return (NULL);
	head = c;
	i = 0;
	while (head->next && i++ < pos)
		head = head->next;
	if (i != pos)
		return (NULL);
	return (head);
}

char	*get_stat_name(t_stat_type stat)
{
	char	*stats[] = {"", "intelligence", "strength", "perception", "charisma", "stealth", "speed"};
	return (stats[stat]);
}

int get_char_stat(t_char *c, t_stat_type stat)
{
    if (stat == STAT_INTELLIGENCE)
        return (c->intelligence);
    if (stat == STAT_STRENGTH)
        return (c->strength);
    if (stat == STAT_PERCEPTION)
        return (c->perception);
    if (stat == STAT_CHARISMA)
        return (c->charisma);
    if (stat == STAT_STEALTH)
        return (c->stealth);
    if (stat == STAT_SPEED)
        return (c->speed);
    return (0);
}

t_item	*copy_item_by_id(t_item *src, unsigned long id)
{
	t_item	*head;
	t_item	*ret;

	if (!src)
	{
		if (DEBUG)
			printf("DEBUG: copy_item_by_id return at start\n");
		return (NULL);
	}
	head = src;
	while (head && head->id != id)
		head = head->next;
	if (!head)
	{
		if (DEBUG)
			printf("DEBUG: copy_item_by_id !head\n");
		return (NULL);
	}
	ret = init_item(head->id, head->name, head->description, head->type, head->value, head->stat, head->c_stat, head->stat_mult, head->can_drop);
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

t_item	*get_item_by_name(t_item *src, char *name)
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
			dst = init_item(head->id, head->name, head->description, head->type, head->value, head->stat, head->c_stat, head->stat_mult, head->can_drop);
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
