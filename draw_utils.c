/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:13:17 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/16 12:32:31 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int get_sign(int x)
{
	if (x > 0)
		return (1);
	else if (x < 0)
		return (-1);
	else
		return (0);
}

void	bresenham(t_line *newline, mlx_image_t* image, t_point start, t_point end)
{
	int i;

	i = 0;
	newline->p = 2 * newline->dy - newline->dx;
	while (i < newline->dx)
	{
		draw_pixel(image, start.x, start.y, newline->col);
		while(newline->p >= 0)
		{
			newline->p = newline->p - 2 * newline->dx;
			if (newline->swapped)
				start.x += get_sign(end.x - start.x);
			else
				start.y += get_sign(end.y - start.y);
		}
		newline->p = newline->p + 2 * newline->dy;
		if (newline->swapped)
			start.y += get_sign(end.y - start.y);
		else
			start.x += get_sign(end.x - start.x);
		i++;
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