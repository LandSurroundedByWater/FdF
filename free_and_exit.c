/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:27:02 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/19 12:56:24 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

void	ft_free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_free_map_and_array_error(t_map *map, char **array, char *error)
{
	int	i;

	i = 0;
	perror(error);
	ft_free_double_array(array);
	while (i < map->rows)
	{
		free(map->points[i]);
		i++;
	}
	free(map->points);
	free(map->start);
	free(map->end);
	free(map);
	map = NULL;
	exit(1);
}

void	ft_free_map_and_error(t_map *map, char *error)
{
	int	i;

	i = 0;
	perror(error);
	while (i < map->rows)
	{
		free(map->points[i]);
		i++;
	}
	free(map->points);
	free(map->start);
	free(map->end);
	free(map);
	map = NULL;
	exit(1);
}

void	ft_free_map_and_exit(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		free(map->points[i]);
		i++;
	}
	free(map->points);
	free(map->start);
	free(map->end);
	free(map);
	map = NULL;
	exit(0);
}
