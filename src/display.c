#include "../includes/space.h"

void	display_location(t_data *data)
{
	t_location	*location;
	int			option;
	int			i;

	if (!data)
		return ;
	location = data->current_location;
	option = -1;
	while (option <= 0 || option > i)
	{
		//clear_console();
		printf("location: %s | x: %i y: %i\n\n%s\n\noptions:\n", location->name, location->x, location->y, location->description);
		i = 0;
		while (location->options[i])
		{
			printf("%i: %s\n", i + 1, location->options[i]);
			i++;
		}
		option = get_input_int("");
		if (option <= 0 || option > i)
			get_input("wrong input, press enter to continue...\n");
		else 
			handle_location_option(data, location, option - 1);
	}
}

void	display_item(t_item *item)
{
	printf("name: %s\n", item->name);
	printf("-------------------\n");
	printf("type: %s\n", item->description);
	printf("-------------------\n");
	printf("description: %s\n", item->description);
	printf("-------------------\n");
	printf("stat: %i\n", item->stat);
}

void	display_inventory_range(t_item *item, int start, int end)
{
	t_item	*head;
	int		i;
	char	*name;
	char	*type;

	if (!item)
		return ;
	head = item;
	printf("#  | name     | type     | stat\n");
	while (start <= end && head)
	{
		name = format_width(head->name, 10);
		type = format_width(head->type, 10);
		printf("%i: %s %s %i\n", start, name, type, head->stat);
		free(name);
		free(type);
		start++;
		head = head->next;
	}
	return (start);
}

void	display_inventory(t_data *data, t_inventory *inv)
{
	t_item	*tmp;
	t_item	*selectedItem;
	int		option;
	int		i;
	int		j;
	int		displaySize = 10;
	char	*options[4] = NULL;

	if (!inv)
		return ;
	input = -1;
	i = 1;
	tmp = inv->item;
	while (option < 1)
	{
		j = 1;
		i = display_inventory_range(tmp, i, i + displaySize);
		options[0] = "select item";
		if (i > displaySize)
		{
			options[j] = "prev";
			j++;
		}
		if (i + displaySize < inv->maxSize)
		{
			options[j] = "next";
			j++;
		}
		options[j] = "back";
		printf("options:\n");
		j = 0;
		while (options[j])
		{
			printf("%i: %s\n", j + 1, options[j]);
			j++;
		}
		option = get_input_int("");
		if (option < 1 || option > j)
		{
			get_input_int("wrong input\n");
			option = -1;
		}
		option--;
		if (!strcmp(options[option], "select item"))
		{
			option = get_input_int("enter number");
			if (option >= 1 && option <= inv->maxSize)
			{
				selectedItem = get_item_by_pos(inv, option);
				display_item(selectedItem);
				get_input_int("press enter to continue...");
			}
		}
		if (!strcmp(options[option], "prev"))
		{
			i -= (displaySize * 2);
			if (i < 1)
				i = 1;
			option = -1;
		}
		else if (!strcmp(options[option], "next"))
			option = -1;
		else if (!strcmp(options[option], "back"))
			break;
	}
}
