#include "../includes/space.h"

void	read_location(t_location *location, FILE *fd)
{
	char	*line = NULL;
	size_t	len = 0;
	int		part = 0;
	int		i;
	char	*ai;

	int	read = 1;
	while (read > -1)
	{
		read = getline(&line, &len, fd);
		if (read == -1)
		{
			free(line);
			free_location(location);
			return ;
		}
		if (line[read - 1] == '\n')
			read--;
		if (!strncmp(line, "-end-", read))
			break ;
		if (part == 0)
		{
			location->name = ft_substr(line, 0, read);
			if (!location->name)
			{
				free(line);
				free_location(location);
				return ;
			}
		}
		else if (part == 1)
		{
			location->description = ft_substr(line, 0, read);
			if (!location->description)
			{
				free(line);
				free_location(location);
				return ;
			}
		}
		else if (part == 2)
		{
			ai = ft_substr(line, 0, read);
			i = atoi(ai);
			free(ai);
			location->options = (char **)malloc(sizeof(char *) * (i + 2));
			if (!location->options)
			{
				free(line);
				free_location(location);
				return ;
			}
			i = 0;
		}
		else
		{
			location->options[i] = ft_substr(line, 0, read);
			if (!location->options[i])
			{
				free(line);
				free_location(location);
				return ;
			}
			i++;
		}
		part++;
	}
	location->options[i] = NULL;
	free(line);
}
