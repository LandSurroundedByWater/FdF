/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/18 11:39:26 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_translate_keyhook(t_map *map)
{
	if (mlx_is_key_down(map->m, MLX_KEY_UP))
		map->origoy -= 20;
	if (mlx_is_key_down(map->m, MLX_KEY_DOWN))
		map->origoy += 20;
	if (mlx_is_key_down(map->m, MLX_KEY_RIGHT))
		map->origox += 20;
	if (mlx_is_key_down(map->m, MLX_KEY_LEFT))
		map->origox -= 20;
	draw_map(map);
}

static void	my_rotate_keyhook(t_map *map)
{
	if (mlx_is_key_down(map->m, MLX_KEY_W))
		map->projection.alpha += 0.03;
	if (mlx_is_key_down(map->m, MLX_KEY_S))
		map->projection.alpha -= 0.03;
	if (mlx_is_key_down(map->m, MLX_KEY_D))
		map->projection.beta += 0.03;
	if (mlx_is_key_down(map->m, MLX_KEY_A))
		map->projection.beta -= 0.03;
	if (mlx_is_key_down(map->m, MLX_KEY_Q))
		map->projection.gamma -= 0.03;
	if (mlx_is_key_down(map->m, MLX_KEY_E))
		map->projection.gamma += 0.03;
	my_translate_keyhook(map);
}

void	my_keyhook(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->m, MLX_KEY_ESCAPE))
		ft_free_map_and_exit(map);
	if (mlx_is_key_down(map->m, MLX_KEY_P))
		change_projection(map);
	if (mlx_is_key_down(map->m, MLX_KEY_EQUAL))
		map->z_factor += 0.05;
	if (mlx_is_key_down(map->m, MLX_KEY_MINUS))
		map->z_factor -= 0.05;
	if (mlx_is_key_down(map->m, MLX_KEY_1))
		change_color_theme(map, 1);
	if (mlx_is_key_down(map->m, MLX_KEY_2))
		change_color_theme(map, 2);
	if (mlx_is_key_down(map->m, MLX_KEY_3))
		change_color_theme(map, 3);
	my_rotate_keyhook(map);
}

static void	re_config_map(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->cols)
		{
			map->points[j][i].x = i * map->pic_width;
			map->points[j][i].y = j * map->pic_height;
			i++;
		}
		j++;
	}
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_map	*map;

	map = param;
	(void) xdelta;
	if (ydelta > 0 && map->size_factor > 0)
		map->size_factor -= 0.1;
	else if (ydelta < 0 && map->size_factor < 10)
		map->size_factor += 0.1;
	map->pic_width = map->pic_size_related / map->cols * map->size_factor;
	map->pic_height = map->pic_size_related / map->rows * map->size_factor;
	re_config_map(map);
	draw_map(map);
}
