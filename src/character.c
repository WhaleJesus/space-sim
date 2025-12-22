#include "../includes/space.h"

void	character_heal(t_char *c, int amount)
{
	if (c->hp + amount > c->hp_max)
		amount = c->hp_max - c->hp;
	c->hp += amount;
	printf("%s healed %ihp\n", c->name, amount);
	get_input_int("");
}

int	character_take_damage(t_char *c, int amount)
{
	if (c->hp - amount < 0)
		amount = c->hp;
	c->hp -= amount;
	printf("%s took %i damage\n", c->name, amount);
	if (c->hp == 0)
	{
		c->dead = 1;
		printf("%s has died\n", c->name);
		return (0);
	}
	return (1);
}

void	character_add_xp(t_char *c, unsigned long xp, int display)
{
	int	lvlup;
	unsigned long	add;
	
	if (display)
		printf("%s gained %lu xp.\n", c->name, xp);
	lvlup = 0;
	while (c->xp + xp >= c->xp_to_next_lvl)
	{
		add = xp;
		if (c->xp + xp > c->xp_to_next_lvl)
		{
			add = c->xp_to_next_lvl - c->xp;
		}
		xp -= add;
		c->xp += add;
		if (c->xp >= c->xp_to_next_lvl)
		{
			c->xp = 0;
			c->xp_to_next_lvl += 25;
			c->skill_points += 1;
			lvlup++;
		}
	}
	c->xp += xp;
	if (display)
	{
		if (lvlup > 1)
			printf("%s gained %i skill points!\n", c->name, lvlup);
		else if (lvlup)
			printf("%s has gained a skill point!\n", c->name);
	}
}

int	character_increment_stat(t_char *c, char *stat, int add)
{
	if (!strcmp(stat, "intelligence"))
		c->intelligence += add;
	else if (!strcmp(stat, "strength"))
		c->strength += add;
	else if (!strcmp(stat, "perception"))
		c->perception += add;
	else if (!strcmp(stat, "charisma"))
		c->charisma += add;
	else if (!strcmp(stat, "stealth"))
		c->stealth += add;
	else if (!strcmp(stat, "speed"))
		c->speed += add;
	else 
		return (0);
	return (1);
}

int	character_change_stat(t_char *c, char *stat, int add)
{
	if (!strcmp(stat, "intelligence"))
		c->intelligence = add;
	else if (!strcmp(stat, "strength"))
		c->strength = add;
	else if (!strcmp(stat, "perception"))
		c->perception = add;
	else if (!strcmp(stat, "charisma"))
		c->charisma = add;
	else if (!strcmp(stat, "stealth"))
		c->stealth = add;
	else if (!strcmp(stat, "speed"))
		c->speed = add;
	else 
		return (0);
	return (1);
}
