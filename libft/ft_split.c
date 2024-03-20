/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:51:06 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/18 16:14:50 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	string_length(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static char	**free_array(char **array, size_t count)
{
	while (count > 0)
	{
		free(array[count]);
		count--;
	}
	free(array);
	return (NULL);
}

static size_t	count_strings(const char *s, char c)
{
	size_t	strings;

	strings = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			strings++;
			while (*s != c && *s != '\0')
			{
				s++;
			}
		}
		else
		{
			s++;
		}
	}
	return (strings);
}

static void	*get_word(size_t len, const char *s)
{
	size_t	j;
	char	*str;

	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = -1;
	while (++j < len)
		str[j] = s[j];
	str[len] = '\0';
	return (str);
}

char	**ft_split(const char *s, char c)
{
	size_t	strings;
	size_t	i;
	size_t	len;
	char	**return_array;

	i = 0;
	strings = count_strings(s, c);
	return_array = (char **)malloc((strings + 1) * sizeof(char *));
	if (!return_array)
		return (NULL);
	while (*s != '\0' && i < strings)
	{
		if (*s != c)
		{
			len = string_length(s, c);
			return_array[i] = get_word(len, s);
			if (!return_array[i])
				free_array(return_array, i);
			s += len;
			i++;
		}
		s++;
	}
	return_array[i] = NULL;
	return (return_array);
}
