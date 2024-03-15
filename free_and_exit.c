/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:27:02 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/15 14:39:20 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

void	ft_free_double_and_error(char **arr, char *error)
{
	int	i;

	i = 0;
	while (!arr[i])
		free(arr[i]);
	free(arr);
	perror(error);
	exit(1);
}
void	ft_free_single_and_error(char *arr, char *error)
{
	free(arr);
	perror(error);
	exit(1);
}


void	ft_free_map_and_error(t_map *map, char *error)
{
	int i;

    i = 0;
    while (i < map->rows)
	{
        free(map->points[i]);
		i++;
    }
	free(map->points);
	free(map->start);
	free(map->end);
	mlx_terminate(map->mlx);
	free(map);
	perror(error);
	exit(1);
}
void	ft_free_map(t_map *map)
{
	int i;

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
}

void ft_free_double_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void ft_free_double_array_content(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
}