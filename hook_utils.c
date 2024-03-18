/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:37:46 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/18 11:41:02 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_color_theme(t_map *map, int theme)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->cols)
		{
			map->points[j][i].col_theme = theme;
			i++;
		}
		j++;
	}
}

void	change_projection(t_map *map)
{
	if (map->projection.is_iso == true)
	{
		map->projection.alphasave = map->projection.alpha;
		map->projection.betasave = map->projection.beta;
		map->projection.gammasave = map->projection.gamma;
		map->projection.alpha = 0;
		map->projection.beta = 0;
		map->projection.gamma = 0;
		map->projection.is_iso = false;
	}
	else
	{
		map->projection.alpha = map->projection.alphasave;
		map->projection.beta = map->projection.betasave;
		map->projection.gamma = map->projection.gammasave;
		map->projection.is_iso = true;
	}
}
