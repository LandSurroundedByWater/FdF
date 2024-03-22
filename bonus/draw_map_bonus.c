/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:14:51 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/22 14:52:30 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

int	pixel_ok(int x, int y)
{
	if (x < WIDTH && x > 0 && y < HEIGHT && y > 0)
		return (1);
	return (-1);
}

void	draw_line(mlx_image_t *image, t_map *map, t_point *start, t_point *end)
{
	int32_t	col;

	col = get_col(start, end, map);
	*start = rotate(*start, map);
	*end = rotate(*end, map);
	*start = correct_point_offset(start, map);
	*end = correct_point_offset(end, map);
	start->dx = absolute_value(end->x - start->x);
	start->dy = absolute_value(end->y - start->y);
	start->err = start->dx - start->dy;
	bresenham_line(image, *start, *end, col);
	if (pixel_ok(end->x, end->y) > 0)
		mlx_put_pixel(image, end->x, end->y, get_col(start, end, map));
}

static void	draw_background(mlx_image_t *image, int32_t col)
{
	int	x;
	int	y;

	x = 0;
	while (x < (int)image->width)
	{
		y = -1;
		while (++y < HEIGHT)
			mlx_put_pixel(image, x, y, col);
		x++;
	}
}

static void	draw_lines(t_map *map, mlx_image_t *newimage)
{
	int	i;
	int	j;

	j = -1;
	set_offset(map);
	while (++j < map->rows)
	{
		i = -1;
		while (++i < map->cols)
		{
			if (i < map->cols - 1)
			{
				init_points(map->start, map->points[j][i], map->end, \
				map->points[j][i + 1]);
				draw_line(newimage, map, map->start, map->end);
			}
			if (j < map->rows - 1)
			{
				init_points(map->start, map->points[j][i], map->end, \
				map->points[j + 1][i]);
				draw_line(newimage, map, map->start, map->end);
			}
		}
	}
}

void	draw_map(t_map *map)
{
	mlx_image_t	*newimage;
	mlx_image_t	*temp;

	if (map->origoy >= HEIGHT - (HEIGHT / 6) || map->origoy <= 0 + (HEIGHT / 6) \
	|| map->origox >= WIDTH - (WIDTH / 8) || map->origox <= 0 + (WIDTH / 8))
		map->change = 0;
	newimage = mlx_new_image(map->m, WIDTH, HEIGHT);
	if (!map->image)
		ft_free_map_and_error(map, ERR_MLX);
	if (mlx_image_to_window(map->m, newimage, 0, 0) == -1)
		ft_free_map_and_error(map, ERR_MLX);
	draw_background(newimage, COL_BG);
	draw_lines(map, newimage);
	temp = map->image;
	map->image = newimage;
	mlx_delete_image(map->m, temp);
}
