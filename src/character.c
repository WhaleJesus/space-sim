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
