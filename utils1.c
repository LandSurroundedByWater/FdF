/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:44:14 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/15 13:00:11 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_hexa(char c)
{
	if (c == 'a' || c == 'A')
		return (10);
	else if (c == 'b' || c == 'B')
		return (11);
	else if (c == 'c' || c == 'C')
		return (12);
	else if (c == 'd' || c == 'D')
		return (13);
	else if (c == 'e' || c == 'E')
		return (14);
	else if (c == 'f' || c == 'F')
		return (15);
	return (c - 48);
}

int32_t	ft_atoi_hex(char *str)
{
	int32_t		i;
	int32_t		result;
	char		*str2;

	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	str2 = ft_strjoin(str, "FF");
	i = 0;
	result = 0;
	while (str2[i] == '0' || str2[i] == 'x')
		i++;
	while (str2[i])
	{
		result *= 16;
		result = result + is_hexa(str2[i]);
		i++;
	}
	free(str2);
	return (result);
}
/*int count_words(char *str, char c)
{
	int splits;
	int i;

	i = 0;
	splits = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			splits++;
        i++;
	}
	splits++;
	return(splits);
}*/


void free_and_exit(char **array)
{
    if (array == NULL) {
        return;
    }
	int i;
	i = 0;
    while (array[i] != NULL)
	{
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
	exit (1);
}
/*void next_string(char *str, char c, char **ret, int j)
{
	int i;
	char split[ft_strlen(str)];

	i = 0;
	while(str[i] != 0)
	{
        split[i] = str[i];
		if (str[i] == c)
		{
            split[i] = 0;
			ret[j] = malloc(ft_strlen(split) + 1 * sizeof(char));
			if (!ret[j])
				free_and_exit(ret);
            ft_strlcpy(ret[j], split, ft_strlen(split) + 1);
			j++;
			str = &str[i + 1];
			i = -1;
		}
		i++;
	}
	ret[j] = malloc(ft_strlen(split) + 1 * sizeof(char));
	if (!ret[j])
		free_and_exit(ret);
	ft_strlcpy(ret[j++], split, ft_strlen(split) + 1);
	ret[j] = 0;
}

char **ft_split_fdf(char *str, char c)
{
	int j;
	int splits;
	char **ret;

	j = 0;
	splits = count_words(str, c);
	ret = (char **)malloc((splits + 1) * sizeof(char *));
	if (!ret)
		free_and_exit(ret);
	next_string(str, c, ret, j);
	return (ret);
}*/

/*static size_t	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

char	**ft_split_fdf(char const *s, char c)
{
	char	**lst;
	size_t	word_len;
	int		i;

	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!s || !lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			lst[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
}*/


void print_map(t_map *map)
{
	int i;
	int j;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->cols)
		{

			printf("%d ", map->points[j][i].z);
			//printf("%d (%d,%d), -%X- | ", map->points[j][i].z, map->points[j][i].y, map->points[j][i].x, map->points[j][i].col);
			i++;
		}
		printf("\n");
		j++;
	}

}
