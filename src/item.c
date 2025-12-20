#include "../includes/space.h"

void	print_inventory(t_inventory *inv)
{
	t_item	*head;

	if (!inv || !inv->item)
		return ;
	head = inv->item;
	int	i = 1;
	while (head)
	{
		printf("%i %s\n", i, head->name);
		i++;
		head = head->next;
	}
}

int	equip_weapon_from_inv(t_char *c, t_inventory *inv, unsigned long id)
{
	t_item	*head;

	if (!c || !inv)
		return (0);
	head = inv->item;
	while (head && head->id != id)
		head = head->next;
	if (!head)
		return (0);
	if (head->id == id)
	{
		if (c->weapon)
			c->weapon->equipped = 0;
		head->equipped = 1;
		c->weapon = head;
		return (1);
	}
	return (0);
}

int	unequip_weapon(t_char *c) 
{
	t_item	*head;

	if (!c || !c->inventory || !c->inventory->item || !c->weapon)
		return (0);
	head = c->inventory->item;
	while (head)
	{
		if (strstr(head->name, "fist") || strstr(head->name, "claw"))
			break ;
		head = head->next;
	}
	if (!head)
		return (0);
	equip_weapon_from_inv(c, c->inventory, head->id);
	return (1);
}

void	add_item(t_item *dst, t_item *item)
{
	t_item	*head;
	t_item	*tmp;

	if (!dst || !item)
		return ;
	head = dst;
	while (head->next && strcmp(item->type, head->type))
	head = head->next;
	while (head->next && head->next->stat < item->stat)
		head = head->next;
	tmp = head->next;
	head->next = item;
	item->prev = head;
	if (tmp)
	{
		tmp->prev = item;
		item->next = tmp;
	}
}

int	inventory_add_item(t_inventory *inv, t_item *item)
{
	if (!inv || !item)
		return (-1);
	if (inv->size >= inv->maxSize && inv->maxSize != -1)
	{
		printf("Inventory full.\n");
		return (0);
	}
	if (!inv->item)
		inv->item = item;
	else 
	{
		add_item(inv->item, item);
	}
	inv->size++;
	return (1);
}

int	inventory_remove_item(t_inventory *inv, unsigned long id)
{
	t_item	*head;
	t_item	*tmp;

	if (!inv || !inv->item)
		return (0);
	head = inv->item;
	while (head && head->id != id)
	{
		tmp = head;
		head = head->next;
	}
	if (!head)
		return (0);
	if (!head->can_drop)
		return (0);
	tmp->next = head->next;
	if (head->next)
		head->next->prev = tmp;
	free_item(head);
	inv->size--;
	return (1);
}

int	item_stat(t_char *c, t_item *item)
{
	int	stat;
	int	c_stat;

	if (!c || !item)
		return (0);
	stat = item->stat;
	if (!item->c_stat)
		return (stat);
	if (!strcmp(item->c_stat, "intelligence"))
		c_stat = c->intelligence;
	else if (!strcmp(item->c_stat, "strength"))
		c_stat = c->strength;
	else if (!strcmp(item->c_stat, "perception"))
		c_stat = c->perception;
	else if (!strcmp(item->c_stat, "charisma"))
		c_stat = c->charisma;
	else if (!strcmp(item->c_stat, "stealth"))
		c_stat = c->stealth;
	else if (!strcmp(item->c_stat, "speed"))
		c_stat = c->speed;
	else 
		c_stat = 0;
	stat += c_stat * item->stat_mult;
	return (stat);
}
