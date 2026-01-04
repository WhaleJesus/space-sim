#include "../includes/space.h"

void	display_location(t_data *data)
{
	t_location	*location;
	t_option	**options;
	int			option;
	int			i;
	int			owned = 0;

	if (!data || !data->current_location)
		return ;
	location = data->current_location;
	option = -1;
	if (location->characters)
	{
		owned = 1;
		options = add_option_no_free(location->options, "talk", 0, 0, STAT_NONE, 0);
	}
	if (location->can_build)
		options = add_option(options, "build", 0, 0, STAT_NONE, 0);
	else 
		options = location->options;
	while (option <= 0 || option > i)
	{
		if (!DEBUG)
			clear_console();
		printf("location: %s | x: %i y: %i\n\n%s\n\noptions:\n", location->name, location->x, location->y, location->description);
		i = 0;
		while (options[i])
		{
			printf("%i: %s\n", i + 1, options[i]->text);
			i++;
		}
		option = get_input_int("");
		if (option < 0 || option > i)
			get_input_int("wrong input, press enter to continue...\n");
		else 
			handle_location_option(data, location, options, option - 1);
	}
	if (owned)
		free_option_array(options);
}

void	display_item(t_data *data, t_char *c, t_inventory *inv, t_item *item, int party, int trade)
{
	char	*options[5];
	int		j = 0;
	int		option = -1;
	
	while (option == -1)
	{
		j = -1;
		if (!DEBUG)
			clear_console();
		printf("name: %s\n", item->name);
		printf("-------------------\n");
		printf("type: %s\n", item->type);
		printf("-------------------\n");
		printf("description: %s\n", item->description);
		printf("-------------------\n");
		printf("stat: %i\n\n", item->stat);
		printf("-------------------\n");
		printf("value: %i\n\n", item->value);

		if (party)
		{
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
		}
		if (trade == 1 && item->value >= 0)
		{
			if (party)
				options[++j] = "sell";
			else 
				options[++j] = "buy";
		}
		else if (trade == 2)
			options[++j] = "take";
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
				int	stat = item_stat(c, item);
				character_heal(c, stat);
				inventory_remove_item(c->inventory, item->id);
			}
			else if (!strcmp(options[option], "sell"))
				character_trade_item(c, data->char_main, item);
			else if (!strcmp(options[option], "buy"))
				character_trade_item(data->char_main, c, item);
			else if (!strcmp(options[option], "take"))
				inventory_transfer_item(c->inventory, inv, item->id, 1);
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
	char	*num_long1;

    if (!item)
        return (0);

    head = item;

    while (head && i < start)
    {
        head = head->next;
        i++;
    }

    printf("#  | name       | type       | stat       | value\n");

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
		sprintf(num, "%d", head->stat);
		num_long1 = format_width(num, 10);
        printf("%s| %s | %s | %s | %i \n", num_long, name, type, num_long1, head->value);
        free(name);
		free(tmp);
        free(type);
		free(num_long);
		free(num_long1);
        head = head->next;
        i++;
        printed++;
    }

    return (printed);
}

void	display_inventory(t_data *data, t_char *c, t_inventory *inv, int party, int trade)
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
		printf("%s\n\n%i/%i\n\ngold: %i\n\n", c->name, c->inventory->size, c->inventory->maxSize, data->char_main->gold);
        if (trade)
			printf("%s's gold: %i\n\n", c->name, c->gold);
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
                display_item(data, c, inv, get_item_by_pos(inv->item, idx), party, trade);
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
	if (!DEBUG)
		clear_console();
}

void	display_character(t_char *c) 
{
	int		option;
	int		option2;
	char	*skills[8] = {"intelligence", "strength", "perception", "charisma", "stealth", "speed", "cancel", NULL};

	if (!DEBUG)
		clear_console();	
	printf("name: %s\n\nhp: %i/%i\n\n", c->name, c->hp, c->hp_max);
	printf("xp: %lu/%lu\n", c->xp, c->xp_to_next_lvl);
	if (c->skill_points)
		printf("unassigned skill points: %i\n", c->skill_points);
	printf("\n");
	printf("Intelligence: %i\nStrenght:     %i\nPerception:   %i\nCharisma:     %i\nStealth:      %i\nSpeed:        %i\n\n", c->intelligence, c->strength, c->perception, c->charisma, c->stealth, c->speed);
	printf("weapon: %s\nweapon damage: %i\n\ninventory: %i/%i\n\ngold: %i\n", c->weapon->name, item_stat(c, c->weapon), c->inventory->size, c->inventory->maxSize, c->gold);
	if (c->skill_points)
	{
		option = get_input_int("1. level up\n2. back\n");
		if (option == 1)
		{
			option = -1;
			option2 = -1;
			while (option < 0 && option2 < 0)
			{
				if (!DEBUG)
					clear_console();
				int	len = ptr_arr_len((void **)skills);
				printf("skill points: %i\n", c->skill_points);
				for (int i = 0; i < len; i++)
					printf("%i. %s\n", i + 1, skills[i]);
				option = get_input_int("");
				if (option < 1 || option > len)
				{
					option = -1;
					option2 = -1;
					printf("wrong input\n");
					continue ;
				}
				option--;
				if (!strcmp(skills[option], "cancel"))
					break ;
				option2 = 1;
				if (c->skill_points > 1)
					option2 = get_input_int("How many skill points?\n");
				if (option2 < 0 || option2 > c->skill_points)
				{
					option = -1;
					option2 = -1;
					printf("wrong input\n");
					continue ;
				}
				if (!character_increment_stat(c, skills[option], option2))
					printf("stat doesn't exist, learn how to type\n");
				else 
					c->skill_points -= option2;
			}
			display_character(c);
		}
	}
	else
		option = get_input_int("press enter to go back.\n");
	if (!DEBUG)
		clear_console();
}
