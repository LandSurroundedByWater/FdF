/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:14:51 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/15 11:43:07 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int pixel_ok(int x, int y)
{
	if (x < WIDTH && x > (WIDTH / 6) && y < HEIGHT && y > 0)
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
	if (start->col_theme == 1)
	{
		if(end->z > start->z)
			return (end->col);
		else
			return (start->col);
	}
	else if (start->col_theme == 2)
	{
		if(end->z > start->z)
			return (end->col2);
		else
			return (start->col2);
	}
	else
		return (CLR_JAFFA);
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

void init_line(t_line *line, t_point start, t_point end)
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

void bresenham(t_line *newline, mlx_image_t* image, t_point start, t_point end)
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



void draw_line(mlx_image_t* image, t_map *map, t_point *start, t_point *end)
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
	draw_pixel(image, end->x, end->y, end->col);
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




void draw_background(mlx_image_t* image, int32_t bg_col, int32_t sb_col)
{
	int x;
	int y;

	x = 0;
	while(x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (x < WIDTH / 6)
				draw_bg_pixel(image, x, y, sb_col);
			else
				draw_bg_pixel(image, x, y, bg_col);
		}
		x++;
	}
}
t_point *init_point(t_point *current, t_point orig)
{

	current->col = orig.col;
	current->col2 = orig.col2;
	current->col_theme = orig.col_theme;
	current->x = orig.x;
	current->y = orig.y;
	current->z = orig.z;

	return(current);
}


void draw_map(t_map *map)
{
	mlx_image_t *newimage;
	mlx_image_t *temp;
	if (!(newimage = mlx_new_image(map->mlx, WIDTH, HEIGHT)))
		ft_free_map_and_error(map, ERR_MLX);
	int i;
	int j;

	j = -1;
	if (mlx_image_to_window(map->mlx, newimage, 0, 0) == -1)
			ft_free_map_and_error(map, ERR_MLX);
	draw_background(newimage, BG_COLOR, SB_COLOR);
	//my_put_string(map, 20, 200);
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
	temp = map->image;
	map->image = newimage;
	mlx_delete_image(map->mlx, temp);
}

/*void draw_map(t_map *map)
{
	int i;
	int j;

	j = -1;
	my_put_string(map, 20, 200);
	draw_background(map->image, BG_COLOR, SB_COLOR);
	while (++j < map->rows)
	{
		i = -1;
		while (++i < map->cols)
		{
			if (i < map->cols - 1)
			{
				init_points(map->start, map->points[j][i], map->end, map->points[j][i + 1]);
				draw_line(map->image, map, map->start, map->end);
			}
			if (j < map->rows - 1)
			{
				init_points(map->start, map->points[j][i], map->end, map->points[j + 1][i]);
				draw_line(map->image, map, map->start, map->end);
			}
		}
	}
}*/


/*int sign(int x)
{
	if(x>0)
		return 1;
	else if(x<0)
		return -1;
	else
		return 0;
}


void bres(mlx_image_t* image, t_point p1, t_point p2)
{

	int x,y,dx,dy,swap,temp,s1,s2,p,i,x1,y1,x2,y2;

	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	x=x1;
	y=y1;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	s1=sign(x2-x1);
	s2=sign(y2-y1);
	swap=0;
	draw_pixel(image, x1, y1, 0xFFFFFFFF);
	if(dy>dx)
	{
		temp=dx;
		dx=dy;
		dy=temp;
		swap=1;
	}
	p=2*dy-dx;
	for(i=0;i<dx;i++)
	{
		draw_pixel(image, x, y, 0xFFFFFFFF);
		while(p>=0)
		{
			p=p-2*dx;
			if(swap)
			x+=s1;
			else
			y+=s2;
		}
		p=p+2*dy;
		if(swap)
		y+=s2;
		else
		x+=s1;
	}
	draw_pixel(image, x2, y2, 0xFFFFFFFF);
}*/






/*


	//draw_background(image);
	while (j < map->rows)
	{
		i = 0;
		while (i < map->cols)
		{
			//t_point p1 = map->points[j][i];
			//draw_pixel(image, p1.x, p1.y, p1.col);
			draw_pixel(image, map->points[0][0].x - 2, map->points[0][0].y - 2, 0xFFFFFF);
			draw_pixel(image, map->points[0][0].x + 2, map->points[0][0].y + 2, 0xFFFFFF);
			draw_pixel(image, map->points[0][0].x - 2, map->points[0][0].y + 2, 0xFFFFFF);
			draw_pixel(image, map->points[0][0].x + 2, map->points[0][0].y - 2, 0xFFFFFF);

			draw_pixel(image, map->points[1][0].x - 2, map->points[1][0].y - 2, 0xFFFFFF);
			draw_pixel(image, map->points[1][0].x + 2, map->points[1][0].y + 2, 0xFFFFFF);
			draw_pixel(image, map->points[1][0].x - 2, map->points[1][0].y + 2, 0xFFFFFF);
			draw_pixel(image, map->points[1][0].x + 2, map->points[1][0].y - 2, 0xFFFFFF);

			draw_pixel(image, map->points[0][1].x - 2, map->points[0][1].y - 2, 0xFFFFFF);
			draw_pixel(image, map->points[0][1].x + 2, map->points[0][1].y + 2, 0xFFFFFF);
			draw_pixel(image, map->points[0][1].x - 2, map->points[0][1].y + 2, 0xFFFFFF);
			draw_pixel(image, map->points[0][1].x + 2, map->points[0][1].y - 2, 0xFFFFFF);


			//origo

			draw_pixel(image, map->origox, map->origoy, p1.col);
			draw_pixel(image, map->origox + 2, map->origoy + 2, 0xFF0000FF);
			draw_pixel(image, map->origox - 2, map->origoy - 2, 0xFF0000FF);
			draw_pixel(image, map->origox + 2, map->origoy - 2, 0xFF0000FF);
			draw_pixel(image, map->origox - 2, map->origoy + 2, 0xFF0000FF);
			draw_pixel(image, (map->origox + 3), (map->origoy + 3), 0xFF0000FF);
			draw_pixel(image, (map->origox - 3), (map->origoy - 3), 0xFF0000FF);
			draw_pixel(image, (map->origox + 3), (map->origoy - 3), 0xFF0000FF);
			draw_pixel(image, (map->origox - 3), (map->origoy + 3), 0xFF0000FF);


			//startpoint
			draw_pixel(image, map->startx, map->starty, 0x000000FF);
			draw_pixel(image, (map->startx + 3), (map->starty + 3), 0xFF0000FF);
			draw_pixel(image, (map->startx - 3), (map->starty - 3), 0xFF0000FF);
			draw_pixel(image, (map->startx + 3), (map->starty - 3), 0xFF0000FF);
			draw_pixel(image, (map->startx - 3), (map->starty + 3), 0xFF0000FF);
			i++;
		}
		j++;

	}
*/



/*void correct_offset(t_map *map)
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
}*/


/*void make_iso(t_point point, double angle, t_map *map)
{

	int x = point.x;
	int y = point.y;
	point.x =(x - y) * cos(angle);
	point.y =(x + y) * sin(angle) - ((point.z) * map->z_factor);

}*/