/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:14:13 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/16 12:24:40 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int pixel_ok(int x, int y)
{
	if (x < WIDTH && x > 0 && y < HEIGHT && y > 0)
		return (1);
	return (-1);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
