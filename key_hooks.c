/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:32:39 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/17 20:27:46 by tsaari           ###   ########.fr       */
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
/*static void correct_offset(t_map *map)
{
	int i;
	int j;

	map->offset_y = ((map->points[0][0].y + map->points[map->rows - 1][map->cols - 1].y) / 2);
	map->offset_x = ((map->points[0][0].x + map->points[map->rows - 1][map->cols - 1].x) / 2);
	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->cols)
		{
			map->points[j][i].x = map->points[j][i].x + map->origox - map->offset_x;
			map->points[j][i].y = map->points[j][i].y + map->origoy - map->offset_y;
			i++;
		}
		j++;
	}
}

static void make_iso(t_map *map)
{
	map->projection.alpha = 0;
	map->projection.beta = 0;
	map->projection.gamma = 0;
	map->z_factor = 1;
	int i;
	int j;
	float angle = 0.4;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->cols)
		{
			int x = map->points[j][i].x;
			int y = map->points[j][i].y;
			map->points[j][i].x =(x - y) * cos(angle);
			map->points[j][i].y =(x + y) * sin(angle) - ((map->points[j][i].z) * map->z_factor);
			i++;
		}
		j++;
	}
	map->basic = false;
	correct_offset(map);
}*/



static void	my_translate_keyhook(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
		map->origoy -= 20;
	if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		map->origoy += 20;
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->origox += 20;
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->origox -= 20;
}

static void	my_rotate_keyhook(t_map *map)
{

	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		map->projection.alpha += 0.03;
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		map->projection.alpha -= 0.03;
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		map->projection.beta += 0.03;
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		map->projection.beta -= 0.03;
	if (mlx_is_key_down(map->mlx, MLX_KEY_Q))
		map->projection.gamma -= 0.03;
	if (mlx_is_key_down(map->mlx, MLX_KEY_E))
		map->projection.gamma += 0.03;
}


void	my_keyhook(void *param)
{
	t_map *map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(map->mlx);
		mlx_terminate(map->mlx);
		ft_free_map(map);
		exit(0);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_P))
	{
		change_projection(map);
	}
		
	if (mlx_is_key_down(map->mlx, MLX_KEY_EQUAL))
		map->z_factor += 0.2;
	if (mlx_is_key_down(map->mlx, MLX_KEY_MINUS))
		map->z_factor -= 0.2;
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP) || mlx_is_key_down(map->mlx, MLX_KEY_DOWN) || mlx_is_key_down(map->mlx, MLX_KEY_LEFT) || \
	mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		my_translate_keyhook(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A) || mlx_is_key_down(map->mlx, MLX_KEY_Q) || mlx_is_key_down(map->mlx, MLX_KEY_W) || \
	mlx_is_key_down(map->mlx, MLX_KEY_E) || mlx_is_key_down(map->mlx, MLX_KEY_S) || mlx_is_key_down(map->mlx, MLX_KEY_D))
		my_rotate_keyhook(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_1))
		change_color_theme(map, 1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_2))
		change_color_theme(map, 2);
	if (mlx_is_key_down(map->mlx, MLX_KEY_3))
		change_color_theme(map, 3);
	draw_map(map);
}


static void	re_config_map(t_map *map)
{
	int i;
	int j;

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
	t_map *map;

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
