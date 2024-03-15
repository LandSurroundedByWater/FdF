/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:13:44 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/15 14:41:17 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	count_rows(int fd, t_map *map, char **argv)
{
	int bytes_read;
	char buffer[100000];
	int i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_free_map_and_error(map, ERR_INFILE);
	 while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	 {
		i = 0;
		while(i < bytes_read)
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
	int bytes_read;
	char buffer[100000];
	int i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_free_map_and_error(map, ERR_INFILE);
	 while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	 {
		i = 0;
		while(i < bytes_read || buffer[i] == '\n')
		{
			if (buffer[i] == ' ')
			{
				map->cols++;
				while(buffer[i] == ' ')
					i++;
			}
			if (buffer[i] == '\n')
			{
				close(fd);
				break;
			}
			i++;
		}
	}
	close(fd);
}
/*void	count_rows(int fd, t_map *map, char **argv)
{
	int bytes_read;
	char buffer[BUFFER_SIZE];
	int i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_free_map_and_error(map, ERR_INFILE);
	 while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	 {
		i = 0;
		while(i < bytes_read)
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
	int bytes_read;
	static char buffer[100000];
	int i;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_free_map_and_error(map, ERR_INFILE);
	bytes_read = read(fd, buffer, sizeof(buffer));
	i = 0;
	while(i < bytes_read && buffer[i] != '\n')
			i++;

	buffer[i] = 0;
	char **firstarray = ft_split(buffer, ' ');
	if(!firstarray)
	{
		ft_free_map(map);
		ft_free_double_and_error(firstarray, ERR_SPLIT);
	}
	while (*firstarray++ != 0)
		map->cols++;
	close(fd);
	ft_free_double_array_content(firstarray);
}*/


void set_colours(t_point *point)
{
	if (point->z <= 0)
		point->col2 = CLR_SAFFRON;
	else if (point->z < 2)
		point->col2 = CLR_JAFFA;
	else if (point->z < 5)
		point->col2 = CLR_DISCO;
	else if (point->z < 12)
		point->col2 = CLR_FLAMINGO;
	else
		point->col2 = CLR_BRICK_RED;
}

void addrow(t_map *map, char **rowarr, int j)
{
	char **split;
	int i;

	i = 0;
	while(i < map->cols)
	{
		split = ft_split(rowarr[i], ',');
		if (!split)
		{
			ft_free_double_array(rowarr);
			ft_free_map_and_error(map, ERR_MALLOC);
		}
		map->points[j][i].col_theme = 2;
		map->points[j][i].z = ft_atoi(split[0]) * map->z_factor;
		if(map->points[j][i].z > map->highest_z)
			map->highest_z = map->points[j][i].z;
		if (map->points[j][i].z  != 0)
			set_colours(&map->points[j][i]);
		map->points[j][i].x = i * map->pic_width * map->size_factor;
		map->points[j][i].y = j * map->pic_height * map->size_factor;
		if (split[1] != 0)
			map->points[j][i].col = ft_atoi_hex(split[1]);
		else
			map->points[j][i].col = 0xFFFFFF;
		i++;
		ft_free_double_array(split);
	}
}

void	fill_map(int fd, t_map *map, char **argv)
{
	char *row;
	char **rowarr;
	int j;

	j = 0;
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		exit (0);
	while(j < map->rows)
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



void	init_map(int fd, t_map *map, char **argv)
{
	map->cols = 0;
	map->rows = 0;
	map->points = NULL;
	map->projection.alpha = 1.20;
	map->projection.beta = -0.49;
	map->projection.gamma = 0.12;
	map->projection.is_iso = true;
	map->z_factor = 1;
	count_rows(fd, map, argv);
	count_columns(fd, map, argv);
	printf("r %d  c  %d\n", map->rows, map->cols);
	map->size_factor = 1;
	if (HEIGHT > WIDTH)
		map->pic_size_related = WIDTH;
	else
		map->pic_size_related = HEIGHT;
	map->origox = WIDTH / 2 + WIDTH / 12;
	map->origoy = HEIGHT / 2;
	map->pic_width = map->pic_size_related / map->cols;
	map->pic_height = map->pic_size_related / map->rows;
 	map->startx = map->origox - (map->pic_width * map->cols / 2) + map->pic_width / 2;
	map->starty = map->origoy - (map->pic_height * map->rows / 2) + map->pic_height / 2;
}

void	allocate_map(t_map *map)
{
	int i;

	i = 0;
	map->start = malloc(sizeof(t_point));
	map->end = malloc(sizeof(t_point));
	map->points = (t_point **)malloc(map->rows * sizeof(t_point *));
	if (map->points == NULL)
		ft_free_map_and_error(map, ERR_MALLOC);
	while(i < map->rows)
	{
		map->points[i] = (t_point *)malloc((map->cols + 1) * sizeof(t_point));
		if (!map->points[i])
			ft_free_map_and_error(map, ERR_MALLOC);
		i++;
	}
}



/*void	count_columns_and_rows(int fd, t_map *map, char **argv)
{

	map->rows++;
	while(get_next_line(fd) != NULL)
		map->rows++;
	//ft_free_double_array(firstarray);
	free(firstrow);
	close(fd);
}*/