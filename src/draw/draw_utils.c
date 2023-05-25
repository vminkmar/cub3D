/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:27:44 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:27:45 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	pixel_to_grid(int pixel_coordinate, int tile_size)
{
	double	grid_coord;

	grid_coord = pixel_coordinate / tile_size;
	return (grid_coord);
}

int	grid_to_pixel(double grid_coordinate, int grid_size, int pixel_size)
{
	double	pixel_coordinate;

	pixel_coordinate = (grid_coordinate / grid_size) * pixel_size;
	return ((int)pixel_coordinate);
}

t_fvector	angle_to_vector(double angle)
{
	t_fvector	vector;
	double		radians;

	radians = angle * (M_PI / 180.0);
	vector.x = cos(radians);
	vector.y = sin(radians);
	return (vector);
}

void	draw_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
		mlx_put_pixel(img, x, y, color);
}
