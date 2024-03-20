/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:37:46 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/20 13:01:41 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	discomove(t_map *map)
{
	static int	orig_x = 10;
	static int	orig_y = 10;

	if (map->origox + orig_x >= WIDTH - (WIDTH / 8) \
	|| map->origox + orig_x <= 0 + (WIDTH / 8))
	{
		orig_x = -orig_x;
		if (map->col_theme == 6)
			map->col_theme = 3;
		else
			map->col_theme++;
	}
	if (map->origoy + orig_y >= HEIGHT - (HEIGHT / 6) \
	|| map->origoy + orig_y <= 0 + (HEIGHT / 6))
	{
		orig_y = -orig_y;
		if (map->col_theme == 6)
			map->col_theme = 3;
		else
			map->col_theme++;
	}
	map->origox += orig_x;
	map->origoy += orig_y;
}

void	disco(t_map *map)
{
	if (!map->change)
	{
		map->col_theme = 3;
		map->origox = WIDTH / 2;
		map->origoy = HEIGHT / 2;
		map->change = 1;
	}
	map->projection.alpha += 0.03;
	map->projection.beta += 0.02;
	map->projection.gamma += 0.04;
	discomove(map);
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

int	absolute_value(int num)
{
	if (num < 0)
		return (-num);
	else
		return (num);
}
