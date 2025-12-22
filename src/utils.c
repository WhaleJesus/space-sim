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

int	option_arr_len(t_option **arr)
{
	int	i = 0;

	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

t_option	**add_option(t_option **arr, char *text, int skill_check, int req, t_stat_type type, unsigned long xp)
{
	t_option	**new_arr;
	int			arr_len = option_arr_len(arr);
	int			i = 0;

	if (!arr)
		return (NULL);
	new_arr = malloc(sizeof(t_option *) * (arr_len + 2));
	if (!new_arr)
		return (NULL);
	while (arr[i])
	{
		if (strcmp(arr[i]->text, "exit"))
			new_arr[i] = copy_option(arr[i]);
		else 
			new_arr[i] = init_option(text, skill_check, req, type, xp);
		if (!new_arr[i])
		{
			free_option_array(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = init_option("exit", 0, 0, STAT_NONE, 0);
	if (!new_arr[i])
	{
		free_option_array(new_arr);
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

char	*strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < len1)
		ret[i] = s1[i];
	i = -1;
	while (++i < len2)
		ret[len1 + i] = s2[i];
	ret[len1 + i] = '\0';
	return (ret);
}

char	*format_width(const char *src, size_t size)
{
    char    *out;
    size_t  len;
    size_t  i;

    if (!src || size == 0)
        return NULL;

    out = (char *)malloc(size + 1);
    if (!out)
        return NULL;

    len = strlen(src);

    /* Case 1: string fits */
    if (len <= size)
    {
		for (i = 0; i < len; i++)
			out[i] = src[i];
        for (i = len; i < size; i++)
            out[i] = ' ';
    }
    /* Case 2: string too long */
    else
    {
        if (size <= 3)
        {
			size_t	i = 0;
            while (i < len && i < size)
			{
                out[i] = src[i];
				i++;
			}
			while (i < size)
			{
				out[i] = ' ';
				i++;
			}
        }
        else
        {
			for (i = 0; i < size - 3; i++)
				out[i] = src[i];
            out[size - 3] = '.';
            out[size - 2] = '.';
            out[size - 1] = '.';
        }
    }
    out[size] = '\0';
    return out;
}
