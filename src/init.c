#include "../includes/space.h"

t_item	*init_item(t_data *data, char *name, char *description, char *type, int stat, t_stat_type c_stat, double stat_mult, int can_drop)
{
	t_item			*item;
	unsigned long	id;

	if (!data)
		id = -1;
	else 
		id = data->item_id++;
	item = malloc(sizeof(t_item) + 1);
	if (!item)
		return (NULL);
	item->id = id;
	item->name = ft_strdup(name);
	item->description = ft_strdup(description);
	item->type = ft_strdup(type);
	item->stat = stat;
	item->stat_mult = stat_mult;
	item->c_stat = c_stat;
	item->equipped = 0;
	item->can_drop = can_drop;
	if (!item->name || !item->description || !item->type)
	{
		free_item(item);
		return (NULL);
	}
	item->prev = NULL;
	item->next = NULL;
	return (item);
}

t_inventory	*init_inventory(int maxSize)
{
	t_inventory	*inv;

	inv = malloc(sizeof(t_inventory) + 1);
	if (!inv)
		return (NULL);
	inv->item = NULL;
	inv->size = 0;
	inv->maxSize = maxSize;
	return (inv);
}

t_char	*init_char(t_data *data, char *name, int hp, char *weapon)
{
	t_char	*character = malloc(sizeof(t_char));
	t_item	*fist;

	if (!character)
		return (NULL);
	character->name = ft_strdup(name);
	if (!character->name)
	{
		free_character(character);
		return (NULL);
	}
	character->id = data->npc_id++;
	character->hp = hp;
	character->hp_max = hp;
	character->xp = 0;
	character->xp_to_next_lvl = 100;
	character->xp_on_death = 0;
	character->skill_points = 0;
	character->intelligence = 1;
	character->strength = 1;
	character->perception = 1;
	character->charisma = 1;
	character->stealth = 1;
	character->speed = 1;
	character->dead = 0;
	character->weapon = NULL;
	character->inventory = init_inventory(data->inventory_base_size);
	if (!character->inventory)
	{
		free_character(character);
		return (NULL);
	}
	fist = get_item_by_name(data, data->inventory->item, "fist");
	inventory_add_item(character->inventory, fist);
	character->weapon = fist;
	fist->equipped = 1;
	if (weapon)
	{
		fist = get_item_by_name(data, data->inventory->item, weapon);
		inventory_add_item(character->inventory, fist);
		equip_weapon_from_inv(character, character->inventory, fist->id);
	}
	character->dialogue = NULL;
	character->prev = NULL;
	character->next = NULL;
	return (character);
}

void	init_character_stats(t_char *c, int intelligence, int strength, int perception, int charisma, int stealth, int speed)
{
	character_change_stat(c, "intelligence", intelligence);
	character_change_stat(c, "strength", strength);
	character_change_stat(c, "perception", perception);
	character_change_stat(c, "charisma", charisma);
	character_change_stat(c, "stealth", stealth);
	character_change_stat(c, "speed", speed);
}

void	data_add_char(t_char *c, t_char *add)
{
	t_char *head;

	if (!c || !add)
		return ;
	head = c;
	while (head->next)
		head = head->next;
	head->next = add;
	add->prev = head;
}

t_dialogue	*init_dialogue(t_data *data, char *text)
{
	t_dialogue	*dialogue;

	dialogue = malloc(sizeof(t_dialogue));
	if (!dialogue)
		return (NULL);
	dialogue->text = ft_strdup(text);
	if (!dialogue->text)
	{
		free_dialogue(dialogue);
		return (NULL);
	}
	data->dialogue_id++;
	dialogue->id = data->dialogue_id;
	dialogue->options = NULL;
	dialogue->next = NULL;
	dialogue->prev = NULL;
	return (dialogue);
}

t_option	*init_option(char *text, int skill_check, int req, t_stat_type stat, unsigned long xp)
{
	t_option	*option;

	option = malloc(sizeof(t_option));
	if (!option)
		return (NULL);
	option->text = malloc(sizeof(char) * strlen(text));
	if (!option->text)
	{
		free_option(option);
		return (NULL);
	}
	strcpy(option->text, text);
	option->skill_check = skill_check;
	option->req = req;
	option->stat = stat;
	option->xp = xp;
	return (option);
}

void	init_data_enemies(t_data *data)
{
	data->enemies = init_goblin(data);
}

void	print_locations(t_location *location)
{
	while (location)
	{
		printf("%s x: %i y: %i\n", location->name, location->x, location->y);
		location = location->next;
	}
}

void	init_data_locations(t_data *data)
{
	int			y = 0;
	int			x;
	t_location	*location;

	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			location = init_location_plains(x, y);
			if (!location)
			{
				free_map(data);
				data->exit = 1;
				return ;
			}
			location->prev = NULL;
			location->next = NULL;
			if (!data->map)
				data->map = location;
			else 
			{
				location->prev = data->current_location;
				location->prev->next = location;
			}
			data->current_location = location;
			x++;
		}
		y++;
	}
}

void	init_data_items(t_data *data)
{
	t_item	*item;

	data->inventory = init_inventory(-1);
	if (!data->inventory)
	{
		data->exit = 1;
		return ;
	}
	item = init_item(NULL, "knife", "a small rusty blade", "weapon", 3, STAT_SPEED, 0.5, 1);
	inventory_add_item(data->inventory, item);
	item = init_item(NULL, "fist", "just your bare hands", "weapon", 1, STAT_STRENGTH, 0.5, 0);
	inventory_add_item(data->inventory, item);
	item = init_item(NULL, "apple", "should keep the doctor away", "food", 5, STAT_NONE, 0.0, 1);
	inventory_add_item(data->inventory, item);
}

void	init_data(t_data *data)
{
	data->char_main = NULL;
	data->enemies = NULL;
	data->map = NULL;
	data->map_width = 2;
	data->map_height = 3;
	data->inventory_base_size = 50;
	data->item_id = -1;
	data->dialogue_id = -1;
	data->npc_id = -1;
	data->exit = 0;
	init_data_items(data);
	init_data_enemies(data);
	init_data_locations(data);
	//print_locations(data->map);
}
