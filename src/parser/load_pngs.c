/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_pngs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:48 by vminkmar          #+#    #+#             */
/*   Updated: 2023/06/01 10:44:04 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_wrong_pngs(t_data *data, t_error error)
{
	if (error == ERROR_NORTH)
		print_error("Error\nFailed to load north texture");
	if (error == ERROR_SOUTH)
		print_error("Error\nFailed to load south texture");
	if (error == ERROR_WEST)
		print_error("Error\nFailed to load west texture");
	if (error == ERROR_EAST)
		print_error("Error\nFailed to load east texture");
	if (error == ERROR_DOOR)
		print_error("Error\nFailed to load door texture");
	if (error == ERROR_DOOR_ONE)
		print_error("Error\nFailed to load door texture");
	free_all(data);
	exit(1);
}

void	load_pngs(t_data *data)
{
	t_error	error;

	error = ERROR_NO;
	data->map->tex_north = mlx_load_png(data->map->path_north);
	if (data->map->tex_north == NULL)
		error = ERROR_NORTH;
	data->map->tex_south = mlx_load_png(data->map->path_south);
	if (data->map->tex_south == NULL)
		error = ERROR_SOUTH;
	data->map->tex_west = mlx_load_png(data->map->path_west);
	if (data->map->tex_west == NULL)
		error = ERROR_WEST;
	data->map->tex_east = mlx_load_png(data->map->path_east);
	if (data->map->tex_east == NULL)
		error = ERROR_EAST;
	if (data->map->tex_door[0] != NULL)
		data->map->tex_door[0] = mlx_load_png("./textures/door_green.png");
	if (data->map->tex_door == NULL)
		error = ERROR_DOOR;
	if (data->map->tex_door[1] != NULL)
		data->map->tex_door[1] = mlx_load_png("./textures/door_red.png");
	if (data->map->tex_door == NULL)
		error = ERROR_DOOR_ONE;
	if (error != ERROR_NO)
		print_wrong_pngs(data, error);
}
