/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:51:06 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/18 12:07:20 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	stringlenght(char *sc, char c)
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
}
