/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:13:17 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/22 14:53:22 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_points(t_point *p1, t_point orig1, t_point *p2, t_point orig2)
{
	p1->col = orig1.col;
	p1->col2 = orig1.col2;
	p1->x = orig1.x;
	p1->y = orig1.y;
	p1->z = orig1.z;
	p2->col = orig2.col;
	p2->col2 = orig2.col2;
	p2->x = orig2.x;
	p2->y = orig2.y;
	p2->z = orig2.z;
}

int	get_s(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

void	bresenham_line(mlx_image_t *image, t_point s, t_point e, int32_t col)
{
	int	sx;
	int	sy;
	int	e2;

	sx = get_s(s.x, e.x);
	sy = get_s(s.y, e.y);
	while (s.x != e.x || s.y != e.y)
	{
		if (pixel_ok(s.x, s.y) > 0)
			mlx_put_pixel(image, s.x, s.y, col);
		e2 = 2 * s.err;
		if (e2 > -(s.dy))
		{
			s.err -= s.dy;
			s.x += sx;
		}
		if (e2 < s.dx)
		{
			s.err += s.dx;
			s.y += sy;
		}
	}
}

void	set_offset(t_map *map)
{
	t_point	first;
	t_point	last;

	init_points(&first, map->points[0][0], &last, \
	map->points[map->rows - 1][map->cols - 1]);
	first = rotate(first, map);
	last = rotate(last, map);
	map->offset_y = map->origoy - ((first.y + last.y) / 2);
	map->offset_x = map->origox - ((first.x + last.x) / 2);
}

int32_t	get_col(t_point *start, t_point *end, t_map *map)
{
	if (end->z >= start->z)
		return (end->col);
	else
		return (start->col);
}
