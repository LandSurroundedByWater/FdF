/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:14:51 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/16 10:45:54 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int pixel_ok(int x, int y)
{
	if (x < WIDTH && x > 0 && y < HEIGHT && y > 0)
		return (1);
	return (-1);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_bg_pixel(mlx_image_t* image, int x, int y, int32_t col)
{
	int32_t r = (col>> 24) & 0xFF;
	int32_t g = (col >> 16) & 0xFF;
	int32_t b = (col >> 8) & 0xFF;
	int32_t a = col & 0xFF;

	mlx_put_pixel(image, x, y, ft_pixel(r, g, b, a));
}

void draw_pixel(mlx_image_t* image, int x, int y, int32_t col)
{
	int32_t r = (col>> 24) & 0xFF;
	int32_t g = (col >> 16) & 0xFF;
	int32_t b = (col >> 8) & 0xFF;
	int32_t a = col & 0xFF;

	if (pixel_ok(x, y) > 0)
		mlx_put_pixel(image, x, y, ft_pixel(r, g, b, a));
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

void swap(int *dx, int *dy)
{
		int *temp;

		temp = dx;
		dx = dy;
		dy = temp;
}

int get_sign(int x)
{
	if (x > 0)
		return (1);
	else if (x < 0)
		return (-1);
	else
		return (0);
}

void	init_line(t_line *line, t_point start, t_point end)
{
	int temp;

	line->dx = end.x - start.x;
	line->dy = end.y - start.y;
	line->p = 0;
	line->swapped = 0;
	if(line->dx < 0)
		line->dx *= -1;
	if(line->dy < 0)
		line->dy *= -1;
	if(line->dy > line->dx)
	{
		temp = line->dx;
		line->dx = line->dy;
		line->dy = temp;
		line->swapped = 1;
	}
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

void	draw_line(mlx_image_t* image, t_map *map, t_point *start, t_point *end)
{
	t_line *newline;

	newline = malloc(sizeof(t_line));
	if (!newline)
		ft_free_map_and_error(map, ERR_MALLOC);
	newline->col = get_col(start, end);
	set_offset(map);
	*start = rotate(*start, map);
	*end = rotate(*end, map);
	*start = correct_point_offset(start, map);
	*end = correct_point_offset(end, map);
	init_line(newline, *start, *end);
	bresenham(newline, image, *start, *end);
	draw_pixel(image, end->x, end->y, get_col(start, end));
	free(newline);
}


void	init_points(t_point *p1, t_point orig1, t_point *p2, t_point orig2)
{
	p1->col = orig1.col;
	p1->col2 = orig1.col2;
	p1->x = orig1.x;
	p1->y = orig1.y;
	p1->z = orig1.z;
	p1->col_theme = orig1.col_theme;

	p2->col = orig2.col;
	p2->col2 = orig2.col2;
	p2->x = orig2.x;
	p2->y = orig2.y;
	p2->z = orig2.z;
	p2->col_theme = orig2.col_theme;

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
