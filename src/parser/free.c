/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:22 by vminkmar          #+#    #+#             */
/*   Updated: 2023/06/01 10:43:06 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_textures(t_data *data)
{
	if (data->map->tex_north == NULL || data->map->tex_east == NULL
		|| data->map->tex_west == NULL || data->map->tex_south == NULL
		|| data->map->tex_door[0] == NULL || data->map->tex_door[1] == NULL)
	{
		if (data->map->tex_north != NULL)
			mlx_delete_texture(data->map->tex_north);
		if (data->map->tex_south != NULL)
			mlx_delete_texture(data->map->tex_south);
		if (data->map->tex_west != NULL)
			mlx_delete_texture(data->map->tex_west);
		if (data->map->tex_east != NULL)
			mlx_delete_texture(data->map->tex_east);
		if (data->map->tex_door[0] != NULL)
			mlx_delete_texture(data->map->tex_door[0]);
		if (data->map->tex_door[1] != NULL)
			mlx_delete_texture(data->map->tex_door[1]);
	}
}

void	free_all(t_data *data)
{
	free_list_map(&data->m_list);
	free_list_textures(&data->t_list);
	free_textures(data);
	free_data(data);
	ft_free2d(data->map->map);
	free(data->player);
	free(data->map);
	free(data);
}

void	ft_free2d(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	if (s)
		free(s);
}

void	free_exit(t_data *data)
{
	free(data->player);
	mlx_delete_texture(data->map->tex_north);
	mlx_delete_texture(data->map->tex_south);
	mlx_delete_texture(data->map->tex_west);
	mlx_delete_texture(data->map->tex_east);
	if (data->map->tex_door[0] != NULL)
		mlx_delete_texture(data->map->tex_door[0]);
	if (data->map->tex_door[1] != NULL)
		mlx_delete_texture(data->map->tex_door[1]);
	free(data->map->tex_door);
	free(data->map->path_north);
	free(data->map->path_south);
	free(data->map->path_west);
	free(data->map->path_east);
	free(data->map->floor_color);
	free(data->map->ceiling_color);
	ft_free2d(data->map->map);
	free(data->map);
	mlx_terminate(data->mlx);
	free(data);
}
