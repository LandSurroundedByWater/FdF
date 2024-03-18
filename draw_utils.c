/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:13:17 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/17 10:11:19 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int get_s(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

void bresenham_line(mlx_image_t *image, t_point start, t_point end, int32_t col) 
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	sx = get_s(start.x, end.x);
	sy = get_s(start.y, end.y);
	err = dx - dy;;
    while (start.x != end.x || start.y != end.y) {
        draw_pixel(image, start.x, start.y, col);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            start.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

void	set_offset(t_map *map)
{
	t_point *first;
	t_point *last;

	first = malloc(sizeof(t_point));
	last = malloc(sizeof(t_point));
	init_points(first, map->points[0][0], last, map->points[map->rows - 1][map->cols - 1]);
	*first = rotate(*first, map);
	*last = rotate(*last, map);
	map->offset_y = map->origoy - ((first->y + last->y) / 2);
	map->offset_x = map->origox - ((first->x + last->x) / 2);
	free(first);
	free(last);
}

int32_t get_col(t_point *start, t_point *end)
{
	if (end->col_theme == 1)
	{
		if(end->z >= start->z)
			return (end->col);
		else
			return (start->col);
	}
	else if (end->col_theme == 2)
	{
		if (end->z == 0 && start->z == 0)
			return(COL_LINE2);
		if (end->z < start->z)
			return (start->col2);
		else
			return (end->col2);
	}
	else
		return (COL_JAFFA);
}