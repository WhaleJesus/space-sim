#include "../includes/space.h"

void clear_console(void)
{
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

char	*get_input(char *msg)
{
	char	input[80];
	char	*ret;
	int		i;

	if (!msg)
		msg = "input";
	printf("%s: ", msg);
	fgets(input, sizeof(input), stdin);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\n')
		{
			input[i] = '\0';
			break ;
		}
		i++;
	}
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	strncpy(ret, input, i);
	ret[i] = '\0';
	return (ret);
}

int	get_input_int(char *msg)
{
	char	*input;
	int		i;
	int		ret;

	input = get_input(msg);
	if (strlen(input) == 0)
	{
		free(input);
		return (-1);
	}
	i = 0;
	while (input[i])
	{
		if (!isdigit(input[i]))
		{
			free(input);
			return (-1);
		}
		i++;
	}
	if (atol(input) > INT_MAX || atol(input) < INT_MIN)
		ret = -1;
	else 
		ret = atoi(input);
	free(input);
	return (ret);
}
