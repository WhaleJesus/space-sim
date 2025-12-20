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
