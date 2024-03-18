/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:13:44 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/18 12:15:27 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	count_rows(int fd, t_map *map, char **argv)
{
	int		bytes_read;
	char	buffer[100000];
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_free_map_and_error(map, ERR_INFILE);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				map->rows++;
			i++;
		}
	}
	close(fd);
}

void	count_columns(int fd, t_map *map, char **argv)
{
	int		bytes_read;
	char	buffer;
	int		prev_char;
	int		firstisspace;

	prev_char = '\n';
	firstisspace = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_free_map_and_error(map, ERR_INFILE);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, &buffer, 1);
		if (!firstisspace && buffer == ' ')
			continue ;
		firstisspace = 1;
		if (buffer == ' ' && prev_char != ' ')
			map->cols++;
		else if (buffer == '\n')
			break ;
		prev_char = buffer;
	}
	map->cols++;
	close(fd);
}

static void	set_colours(t_point *point)
{
	if (point->z == 0)
		point->col2 = COL_JAFFA;
	else if (point->z < 2)
		point->col2 = COL_DISCO;
	else if (point->z < 5)
		point->col2 = COL_FLAMINGO;
	else if (point->z < 12)
		point->col2 = COL_BRICK_RED;
	else if (point->z < 60)
		point->col2 = COL_JAFFA;
	else
		point->col2 = COL_SAFFRON;
}

static void	addrow(t_map *map, char **rowarr, int j)
{
	char	**split;
	int		i;

	i = 0;
	while (i < map->cols)
	{
		split = ft_split(rowarr[i], ',');
		if (!split)
			ft_free_map_and_array_error(map, split, ERR_MALLOC);
		map->points[j][i].col_theme = 1;
		map->points[j][i].z = ft_atoi(split[0]) * map->z_factor;
		if (map->points[j][i].z > map->highest_z)
			map->highest_z = map->points[j][i].z;
		if (map->points[j][i].z != 0)
			set_colours(&map->points[j][i]);
		map->points[j][i].x = i * map->pic_width * map->size_factor;
		map->points[j][i].y = j * map->pic_width * map->size_factor;
		if (split[1] != 0)
			map->points[j][i].col = ft_atoi_hex(split[1]);
		else
			map->points[j][i].col = COL_LINE;
		i++;
		ft_free_double_array(split);
	}
}

void	fill_map(int fd, t_map *map, char **argv)
{
	char	*row;
	char	**rowarr;
	int		j;

	j = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit (0);
	while (j < map->rows)
	{
		row = get_next_line(fd);
		if (row < 0)
			ft_free_map_and_error(map, ERR_SPLIT);
		rowarr = ft_split(row, ' ');
		if (!rowarr)
			ft_free_map_and_error(map, ERR_MALLOC);
		free(row);
		addrow(map, rowarr, j);
		ft_free_double_array(rowarr);
		j++;
	}
	close(fd);
}
