/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:24:13 by tsaari            #+#    #+#             */
/*   Updated: 2024/02/16 09:04:59 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void free_double_array(char **array)
{
    if (array == NULL) {
        return; 
    }
	int i;

	i = 0;
    while (array[i] != NULL)
	{
        free(array[i]);
        array[i] = NULL;
    }

    free(array);
}