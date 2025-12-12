#include "../includes/space.h"

void	free_char(t_char *character)
{
	if (character->name)
		free(character->name);
	free(character);
}

void	free_location(t_location *location)
{
	int	i;

	free(location->name);
	free(location->description);
	i = 0;
	while (location->options[i])
	{
		free(location->options[i]);
		i++;
	}
	free(location->options);
	free(location);
}

void	free_map(t_data *data)
{
	t_location	*location;
	t_location	*tmp;

	if (data->map)
	{
		location = data->map;
		while (location)
		{
			tmp = location;
			location = location->next;
			free_location(tmp);
		}
	}
}

void	free_data(t_data *data)
{
	t_char	*tmp;

	free_char(data->char_main);

	while (data->enemies)
	{
		tmp = data->enemies;
		data->enemies = data->enemies->next;
		free_char(tmp);
	}
	free_map(data);
}
