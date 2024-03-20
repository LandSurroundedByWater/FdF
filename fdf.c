/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/19 10:29:35 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_z_factor(t_map *map)
{
	if (map->highest_z > 140)
		map->z_factor = 0.4;
	else if (map->highest_z > 100)
		map->z_factor = 0.8;
}

static void	init_map(int fd, t_map *map, char **argv)
{
	map->cols = 0;
	map->rows = 0;
	map->points = NULL;
	map->projection.alpha = 0.45;
	map->projection.beta = -0.35264;
	map->projection.gamma = 0.45;
	map->projection.is_iso = true;
	map->z_factor = 3;
	map->col_theme = 1;
	count_rows(fd, map, argv);
	count_columns(fd, map, argv);
	map->size_factor = 0.6;
	if (map->cols > 90)
		map->size_factor *= 1.5;
	map->pic_size_related = WIDTH;
	map->origox = WIDTH / 2;
	map->origoy = HEIGHT / 2;
	map->pic_width = map->pic_size_related / map->cols;
	map->pic_height = map->pic_size_related / map->cols;
	map->startx = map->origox - \
	(map->pic_width * map->cols / 2) + map->pic_width / 2;
	map->starty = map->origoy - \
	(map->pic_height * map->rows / 2) + map->pic_height / 2;
}

static void	allocate_map(t_map *map)
{
	int	i;

	i = 0;
	map->start = malloc(sizeof(t_point));
	map->end = malloc(sizeof(t_point));
	map->points = (t_point **)malloc(map->rows * sizeof(t_point *));
	if (map->points == NULL)
		ft_free_map_and_error(map, ERR_MALLOC);
	while (i < map->rows)
	{
		map->points[i] = (t_point *)malloc((map->cols + 1) * sizeof(t_point));
		if (!map->points[i])
			ft_free_map_and_error(map, ERR_MALLOC);
		i++;
	}
}

static void	looper(t_map *map)
{
	mlx_loop_hook(map->m, my_keyhook, map);
	mlx_loop(map->m);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	int		fd;

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
		fill_map(fd, map, argv);
		init_z_factor(map);
		map->m = mlx_init(WIDTH, HEIGHT, argv[1], false);
		if (!map->m)
			ft_free_map_and_error(map, ERR_MLX);
		looper(map);
		mlx_terminate(map->m);
	}
	ft_free_map_and_exit(map);
}
