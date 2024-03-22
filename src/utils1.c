/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:44:14 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/22 14:09:41 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	is_hexa(char c)
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
	int32_t	i;
	int32_t	result;
	char	*str2;

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

int	absolute_value(int num)
{
	if (num < 0)
		return (-num);
	else
		return (num);
}

void	check_array(char **rowarr, t_map *map)
{
	int	i;

	i = 0;
	while (rowarr[i] != NULL && *rowarr[i] != '\n')
		i++;
	if (i != map->cols)
		ft_free_map_and_array_error(map, rowarr, ERR_INFILE);
}
