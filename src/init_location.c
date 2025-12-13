#include "../includes/space.h"

void	init_location_standard(char *name, char *description, int x, int y)
{
	t_location	*location;

	location = malloc(sizeof(t_location) + 1);
	if (!location)
		return (NULL);
	location->name = ft_strdup(name);
	location->description = ft_strdup(description);
	location->options = (char **)malloc(sizeof(char *) * 3);
	if (!location->options)
	{
		free_location(location);
		return (NULL);
	}
	location->options[0] = ft_strdup("move");
	location->options[1] = ft_strdup("exit");
	location->options[2] = NULL;
	location->enemies = NULL;
	location->x = x;
	location->y = y;
	if (!location->name || !location->description || !location->options[0] || !location->options[1])
	{
		free_location(location);
		return (NULL);
	}
	return (location);
}
