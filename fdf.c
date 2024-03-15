/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/15 14:54:58 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_offset(t_map *map)
{
	t_point *first;
	t_point *last;

	first = malloc(sizeof(t_point));
	last = malloc(sizeof(t_point));
	init_point(first, map->points[0][0]);
	init_point(last, map->points[map->rows - 1][map->cols - 1]);
	*first = rotate(*first, map);
	*last = rotate(*last, map);
	map->offset_y = map->origoy - ((first->y + last->y) / 2);
	map->offset_x = map->origox - ((first->x + last->x) / 2);
	free(first);
	free(last);
}


/*void change_color_theme(t_map *map, int theme)
{
	int i;
	int j;

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

void change_projection(t_map *map)
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
static void my_translate_keyhook(t_map *map)
{
	t_map *map;

	map = param;
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->origoy -= 5;
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->origoy += 5;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->origox += 5;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->origox -= 5;
	draw_map(map->image, map);
}

static void my_rotate_keyhook(t_map *map)
{

	map = param;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->projection.alpha += 0.03;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->projection.alpha -= 0.03;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->projection.beta += 0.03;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->projection.beta -= 0.03;
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->projection.gamma -= 0.03;
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->projection.gamma += 0.03;
	draw_map(map->image, map);
}


void	my_keyhook(void *param)
{
	t_map *map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_P))
		change_projection(map);
	if (keydata.key == MLX_KEY_L && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->z_factor += 0.1;
	if (keydata.key == MLX_KEY_K && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		map->z_factor -= 0.1;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		my_translate_keyhook(keydata, map);
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_E \
	|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D )
		my_rotate_keyhook(keydata, map);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		change_color_theme(map, 1);
	if (mlx_is_key_down(map->mlx, MLX_KEY_2))
		change_color_theme(map, 2);
	if (mlx_is_key_down(map->mlx, MLX_KEY_2))
		change_color_theme(map, 3);

	printf("%f\n", map->z_factor);
	draw_map(map->image, map);
}
static void re_config_map(t_map *map)
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
}*/


/*static void my_scrollhook(double xdelta, double ydelta, void *param)
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
	draw_map(map->image, map);
}

*/
void hook(t_map *map)
{
	//mlx_loop_hook(map->mlx, my_loop_hook, map);
	mlx_loop_hook(map->mlx, my_ownkeyhook, map);
	mlx_scroll_hook(map->mlx, my_scrollhook, map);
}

int main(int argc, char **argv)
{
	t_map *map = NULL;
	int fd;
	int fd2;

	fd2 = 1;
	fd = 0;
	if (argc != 2)
		ft_error(ERR_ARG);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error(ERR_MALLOC);
	else
	{
		init_map(fd, map, argv);
		allocate_map(map);
		fill_map(fd2, map, argv);
		map->z_factor = 30 / map->highest_z;
		if (!(map->mlx = mlx_init(WIDTH, HEIGHT, "FDF", false)))
			ft_free_map_and_error(map, ERR_MLX);
		if (!(map->image = mlx_new_image(map->mlx, WIDTH, HEIGHT)))
			ft_free_map_and_error(map, ERR_MLX);
		if (mlx_image_to_window(map->mlx, map->image, 0, 0) == -1)
			ft_free_map_and_error(map, ERR_MLX);
		print_map(map);
		hook(map);
		mlx_loop(map->mlx);
		mlx_terminate(map->mlx);
	}
	ft_free_map(map);
	exit(0);
}





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
/*void make_iso(t_map *map)
{
	int i;
	int j;
	//float angle = START_ANGLE;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->cols)
		{
			int x = map->points[j][i].x;
			int y = map->points[j][i].y;
			map->points[j][i].x =(x - y) * cos(map->alpha);
			map->points[j][i].y =(x + y) * sin(map->alpha) - ((map->points[j][i].z) * map->z_factor);
			i++;
		}
		j++;
	}
}*/


/*void	move_img(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;
	keys_t	key;

	fdf = param;
	key = keydata.key;
	if (key == MLX_KEY_A && keydata.action == MLX_RELEASE
		&& keydata.modifier == MLX_CONTROL)
		puts("Gotta grab it all!");
	if (key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
	if ((key >= 262 && key <= 265))
		set_control_movement(keydata, fdf);
	else if (key == MLX_KEY_T || key == MLX_KEY_I)
		set_control_view(keydata, fdf);
	else if (key == MLX_KEY_N || key == MLX_KEY_M || key == 267
		|| key == 334 || key == 266)
		set_control_height(keydata, fdf);
	else if (key == MLX_KEY_Z || key == MLX_KEY_X)
		set_control_rotation(keydata, fdf);
	else if (key >= MLX_KEY_0 && key <= MLX_KEY_5)
		set_control_palette(keydata, fdf);
	else if (key >= MLX_KEY_B && key <= MLX_KEY_V)
		set_control_point_resolution(keydata, fdf);
}*/
/*void fdf_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}*/





/*static void window_resize(void *ptr)
{
	t_map *map;

	map = ptr;

	if (!(map->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
			ft_free_map_and_error(map, ERR_MLX);

	if (!(map->image = mlx_new_image(map->mlx, WIDTH, HEIGHT)))
			mlx_close_window(map->mlx);

}*/