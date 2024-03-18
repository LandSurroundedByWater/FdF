/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:14:51 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/17 20:28:02 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(mlx_image_t* image, t_map *map, t_point *start, t_point *end)
{
	int32_t col;

	col = get_col(start, end);
	set_offset(map);
	*start = rotate(*start, map);
	*end = rotate(*end, map);
	*start = correct_point_offset(start, map);
	*end = correct_point_offset(end, map);
	bresenham_line(image, *start, *end, col);
	draw_pixel(image, end->x, end->y, get_col(start, end));
}

static void draw_bg_pixel(mlx_image_t* image, int x, int y, int32_t col)
{
	int32_t r = (col>> 24) & 0xFF;
	int32_t g = (col >> 16) & 0xFF;
	int32_t b = (col >> 8) & 0xFF;
	int32_t a = col & 0xFF;
	mlx_put_pixel(image, x, y, ft_pixel(r, g, b, a));
}

static void	draw_background(mlx_image_t* image, int32_t col)
{
	int x;
	int y;
	
	x = 0;
	while(x < (int)image->width)
	{
		y = -1;
		while (++y < HEIGHT)
			draw_bg_pixel(image, x, y, col);
		x++;
	}
}

static void draw_lines(t_map *map, mlx_image_t *newimage)
{
	int i;
	int j;

	j = -1;
	while (++j < map->rows)
	{
		i = -1;
		while (++i < map->cols)
		{
			if (i < map->cols - 1)
			{
				init_points(map->start, map->points[j][i], map->end, map->points[j][i + 1]);
				draw_line(newimage, map, map->start, map->end);
			}
			if (j < map->rows - 1)
			{
				init_points(map->start, map->points[j][i], map->end, map->points[j + 1][i]);
				draw_line(newimage, map, map->start, map->end);
			}
		}
	}
}

void draw_map(t_map *map)
{
	mlx_image_t *newimage;
	mlx_image_t *temp;
	
	if (!(newimage = mlx_new_image(map->mlx, WIDTH, HEIGHT)))
		ft_free_map_and_error(map, ERR_MLX);
	if (mlx_image_to_window(map->mlx, newimage, 0, 0) == -1)
			ft_free_map_and_error(map, ERR_MLX);
	draw_background(newimage, COL_BG);
	draw_lines(map, newimage);
	temp = map->image;
	map->image = newimage;
	mlx_delete_image(map->mlx, temp);
}
