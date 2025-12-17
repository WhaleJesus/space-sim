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
			get_input_int("wrong input, press enter to continue...\n");
		else 
			handle_location_option(data, location, option - 1);
	}
}

void	display_item(t_char *c, t_item *item)
{
	char	*options[5];
	int		j = 0;
	int		option = -1;
	
	while (option == -1)
	{
		j = -1;
		clear_console();
		printf("name: %s\n", item->name);
		printf("-------------------\n");
		printf("type: %s\n", item->type);
		printf("-------------------\n");
		printf("description: %s\n", item->description);
		printf("-------------------\n");
		printf("stat: %i\n\n", item->stat);

		if (item->equipped == 0)
		{
			if (!strcmp(item->type, "weapon"))
				options[++j] = "equip";
			if (item->can_drop)
				options[++j] = "drop";
		}
		else 
			options[++j] = "unequip";
		if (!strcmp(item->type, "food"))
			options[++j] = "eat";
		options[++j] = "back";
		options[++j] = NULL;
		printf("options:\n");
		for (int k = 0; options[k]; k++)
			printf("%i: %s\n", k + 1, options[k]);
		option = get_input_int("");
		if (option < 1 || option > j)
		{
			get_input_int("wrong input, press enter to continue...");
			option = -1;
		}
		else 
		{
			option--;
			if (!strcmp(options[option], "equip"))
				equip_weapon_from_inv(c, c->inventory, item->id);
			else if (!strcmp(options[option], "unequip"))
				unequip_weapon(c);
			else if (!strcmp(options[option], "eat"))
			{
				character_heal(c, item->stat);
				inventory_remove_item(c->inventory, item->id);
			}
			else if (!strcmp(options[option], "drop"))
				inventory_remove_item(c->inventory, item->id);
			else if (!strcmp(options[option], "back"))
				break ;
		}
	}
}

int	display_inventory_range(t_item *item, int start, int page_size)
{
    t_item *head;
    int     i = 1;
    int     printed = 0;
    char    *name;
    char    *type;
	char	num[3];
	char	*num_long;

    if (!item)
        return (0);

    head = item;

    while (head && i < start)
    {
        head = head->next;
        i++;
    }

    printf("#  | name       | type       | stat\n");

    while (head && printed < page_size)
    {
		char	*tmp;
	
		if (head->equipped)
			tmp = strjoin("(e) ", head->name);
		else 
			tmp = ft_strdup(head->name);
        name = format_width(tmp, 10);
        type = format_width(head->type, 10);
		sprintf(num, "%d", i);
		num_long = format_width(num, 3);
        printf("%s| %s | %s | %i\n", num_long, name, type, head->stat);
        free(name);
		free(tmp);
        free(type);
		free(num_long);

        head = head->next;
        i++;
        printed++;
    }

    return (printed);
}

void display_inventory(t_char *c, t_inventory *inv)
{
    int page_start = 1;
    int page_size = 10;
    int printed;
    int option;
    char *options[5];

    if (!inv || inv->size < 1)
    {
        get_input_int("inventory is empty\npress enter to continue...");
        return;
    }

    while (1)
    {
		printf("%s\nWeapon: %s\n\n%i/%i\n", c->name, c->weapon->name, c->inventory->size, c->inventory->maxSize);
        printed = display_inventory_range(inv->item, page_start, page_size);

        int j = 0;
        options[j++] = "select item";

        if (page_start > 1)
            options[j++] = "prev";

        if (page_start + printed - 1 < inv->size)
            options[j++] = "next";

        options[j++] = "back";
        options[j] = NULL;

        printf("options:\n");
        for (int k = 0; options[k]; k++)
            printf("%i: %s\n", k + 1, options[k]);

        option = get_input_int("") - 1;
        if (option < 0 || !options[option])
            continue;

        if (!strcmp(options[option], "select item"))
        {
            int idx = get_input_int("enter number");
            if (idx >= 1 && idx <= inv->size)
                display_item(c, get_item_by_pos(inv->item, idx));
        }
        else if (!strcmp(options[option], "prev"))
        {
            page_start -= page_size;
            if (page_start < 1)
                page_start = 1;
        }
        else if (!strcmp(options[option], "next"))
        {
            page_start += page_size;
        }
        else if (!strcmp(options[option], "back"))
            break;
    }
	clear_console();
}

void	display_character(t_char *c) 
{
	clear_console();
	printf("name: %s\n\nhp: %i/%i\n\nweapon: %s\nweapon damage: %i\n\ninventory: %i/%i\n", c->name, c->hp, c->hp_max, c->weapon->name, c->weapon->stat, c->inventory->size, c->inventory->maxSize);
	get_input_int("press enter to go back.\n");
	clear_console();
}
