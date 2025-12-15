#include "../includes/space.h"

void	add_item(t_item *dst, t_item *item)
{
	t_item	*head;
	t_item	*tmp;
	
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
		item->next = tmp;
		tmp->prev = item;
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
