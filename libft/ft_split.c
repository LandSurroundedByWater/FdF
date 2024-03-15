/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:51:06 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/08 09:43:09 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

static size_t string_length(const char *s, char c) {
    size_t len = 0;
    while (*s != c && *s != '\0') {
        len++;
        s++;
    }
    return len;
}

static void free_array(char **array, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(array[i]);
    }
    free(array);
}

static size_t count_strings(const char *s, char c) {
    size_t strings = 0;
    while (*s != '\0') {
        if (*s != c) {
            strings++;
            while (*s != c && *s != '\0') {
                s++;
            }
        } else {
            s++;
        }
    }
    return strings;
}

char **ft_split(const char *s, char c)
{
	size_t strings;
	size_t i;

	i  = 0;
	strings = count_strings(s, c);
	if (!s)
        return NULL;
    char **return_array = (char **)malloc((strings + 1) * sizeof(char *));
    if (!return_array)
        return NULL;
    while (*s != '\0' && i < strings) {
        if (*s != c) {
            size_t len = string_length(s, c);
            return_array[i] = (char *)malloc((len + 1) * sizeof(char));
            if (!return_array[i]) {
                free_array(return_array, i);
                return NULL;
            }
            for (size_t j = 0; j < len; j++) {
                return_array[i][j] = s[j];
            }
            return_array[i][len] = '\0';
            s += len;
            i++;
        }
        s++;
    }
    return_array[i] = NULL;
    return return_array;
}



/*static size_t	stringlenght(char *sc, char c)
{
	size_t	len;

	len = 0;
	while (*sc != c && *sc != '\0')
	{
		len++;
		sc++;
	}
	return (len);
}

static char	**ft_free(char **s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
	{
		free (s[i]);
		i++;
	}
	free(s);
	return (0);
}
static size_t	countstrings(char const *s, char c)
{
	char	*sc;
	char	*found;
	size_t	strings;

	sc = (char *)s;
	strings = 0;
	while (ft_memchr(sc, c, ft_strlen(sc)))
	{
		found = ft_memchr(sc, c, ft_strlen(sc));
		if ((found - sc) >= 1)
			strings++;
		sc = found + 1;
	}
	if (ft_strlen(sc) > 0)
		strings++;
	return (strings);
}


char	**ft_split(char const *s, char c)
{
	char	*sc;
	char	**returnarray;
	size_t	i;

	sc = (char *)s;
	i = 0;
	if (!s)
		return (0);
	returnarray = (char **)malloc((countstrings(s, c) + 1) * sizeof(char *));
	if (!returnarray)
		return (ft_free(returnarray));
	while (i < countstrings(s, c))
	{
		if (*sc != c)
		{
			returnarray[i] = ft_substr(sc, 0, stringlenght(sc, c));
			if (!returnarray[i])
				return (ft_free(returnarray));
			sc += stringlenght(sc, c) - 1;
			i++;
		}
		sc++;
	}
	returnarray[i] = 0;
	return (returnarray);
}*/
