/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/28 08:12:45 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

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
			map->points[j][i].x = i * map->size_factor;
			map->points[j][i].y = j * map->size_factor;
			i++;
		}
		j++;
	}
}

static void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_map	*map;

	map = param;
	(void) xdelta;
	if (ydelta > 0)
		map->size_factor -= map->size_factor / 10;
	else if (ydelta < 0)
		map->size_factor += map->size_factor / 10;
	re_config_map(map);
}

static void	my_translate_keyhook(t_map *map)
{
	if (map->camera_dir == true)
	{
		if (mlx_is_key_down(map->m, MLX_KEY_UP))
			map->origoy += 10;
		if (mlx_is_key_down(map->m, MLX_KEY_DOWN))
			map->origoy -= 10;
		if (mlx_is_key_down(map->m, MLX_KEY_RIGHT))
			map->origox -= 10;
		if (mlx_is_key_down(map->m, MLX_KEY_LEFT))
			map->origox += 10;
	}
	else if (map->camera_dir == false)
	{
		if (mlx_is_key_down(map->m, MLX_KEY_UP))
			map->origoy -= 10;
		if (mlx_is_key_down(map->m, MLX_KEY_DOWN))
			map->origoy += 10;
		if (mlx_is_key_down(map->m, MLX_KEY_RIGHT))
			map->origox += 10;
		if (mlx_is_key_down(map->m, MLX_KEY_LEFT))
			map->origox -= 10;
	}
	mlx_scroll_hook(map->m, my_scrollhook, map);
	draw_map(map);
}

static void	my_rotate_keyhook(t_map *map)
{
	if (mlx_is_key_down(map->m, MLX_KEY_W))
		map->projection.alpha += 0.02;
	if (mlx_is_key_down(map->m, MLX_KEY_S))
		map->projection.alpha -= 0.02;
	if (mlx_is_key_down(map->m, MLX_KEY_D))
		map->projection.beta += 0.02;
	if (mlx_is_key_down(map->m, MLX_KEY_A))
		map->projection.beta -= 0.02;
	if (mlx_is_key_down(map->m, MLX_KEY_Q))
		map->projection.gamma -= 0.02;
	if (mlx_is_key_down(map->m, MLX_KEY_E))
		map->projection.gamma += 0.02;
	if (mlx_is_key_down(map->m, MLX_KEY_EQUAL))
		map->z_factor += 0.05;
	if (mlx_is_key_down(map->m, MLX_KEY_MINUS))
		map->z_factor -= 0.05;
	if (mlx_is_key_down(map->m, MLX_KEY_END))
	{
		if (map->camera_dir == true)
			map->camera_dir = false;
		else
			map->camera_dir = true;
	}
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
	if (mlx_is_key_down(map->m, MLX_KEY_SPACE))
		disco(map);
	if (mlx_is_key_down(map->m, MLX_KEY_1))
		map->col_theme = 1;
	if (mlx_is_key_down(map->m, MLX_KEY_2))
		map->col_theme = 2;
	if (mlx_is_key_down(map->m, MLX_KEY_3))
		map->col_theme = 3;
	if (mlx_is_key_down(map->m, MLX_KEY_4))
		map->col_theme = 4;
	if (mlx_is_key_down(map->m, MLX_KEY_5))
		map->col_theme = 5;
	if (mlx_is_key_down(map->m, MLX_KEY_6))
		map->col_theme = 6;
	if (mlx_is_key_down(map->m, MLX_KEY_7))
		map->col_theme = 7;
	my_rotate_keyhook(map);
}
