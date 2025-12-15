#include "../includes/space.h"

char* ft_substr(char* arr, int start, int len)
{
	char* str = (char*)malloc(len + 1);
	if (!str)
		return (NULL);
	int i = 0;
	int j = 0;
	while (arr[i])
	{
		if ((i >= start) && (j < len))
		{
			str[j] = arr[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return(str);
}

int	char_arr_len(char **arr)
{
	int	i = 0;

	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

char	**add_option(char **arr, char *option)
{
	char	**new_arr;
	int		arr_len = char_arr_len(arr);
	int		i = 0;

	if (!arr)
		return (NULL);
	new_arr = (char **)malloc(sizeof(char *) * (arr_len + 2));
	if (!new_arr)
		return (NULL);
	while (arr[i])
	{
		if (strcmp(arr[i], "exit"))
			new_arr[i] = ft_strdup(arr[i]);
		else 
			new_arr[i] = ft_strdup(option);
		if (!new_arr[i])
		{
			free_char_array(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = ft_strdup("exit");
	if (!new_arr[i])
	{
		free_char_array(new_arr);
		return (NULL);
	}
	i++;
	new_arr[i] = NULL;
	return (new_arr);
}

int rand_range(int min, int max)
{
    return min + (int)((double)rand() / (RAND_MAX + 1.0) * (max - min + 1));
}

char *ft_strdup(char *s)
{
    char *dup;

    if (!s)
        return NULL;

    dup = (char *)malloc(strlen(s) + 1);
    if (!dup)
        return NULL;

    strcpy(dup, s);
    return dup;
}
