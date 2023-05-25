/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:31 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:28:32 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vairables_the_second(t_data *data)
{
	data->map->tex_south = NULL;
	data->map->map = NULL;
	data->map->map = NULL;
	data->map->color_ceiling = 0;
	data->map->color_ceiling = 0;
	data->map->color_ceiling = 0;
	data->map->color_ceiling = 0;
	data->map->path_east_counter = 0;
	data->map->path_south_counter = 0;
	data->map->path_west_counter = 0;
	data->map->path_north_counter = 0;
	data->map->floor_color_counter = 0;
	data->map->ceiling_color_counter = 0;
	data->map->max_height = 0;
	data->map->max_width = 0;
	data->map->color_floor = 0;
	data->player->counter_p_start = 0;
	data->player->p_start.x = 0;
	data->player->p_start.y = 0;
	data->m_list->empty_line = 0;
	data->t_list->counter = 0;
}

void	init_variables(t_data *data)
{
	data->map->path_east = NULL;
	data->map->path_south = NULL;
	data->map->path_west = NULL;
	data->map->path_north = NULL;
	data->map->floor_color = NULL;
	data->map->ceiling_color = NULL;
	data->map->tex_door[0] = NULL;
	data->map->tex_door[1] = NULL;
	data->map->tex_east = NULL;
	data->map->tex_west = NULL;
	data->map->tex_north = NULL;
	init_vairables_the_second(data);
}
