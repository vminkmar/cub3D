/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:14 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:28:15 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_for_empty_textures(t_data *data)
{
	t_error	error;

	error = ERROR_NO;
	if (data->map->path_east == NULL)
		error = ERROR_EAST;
	else if (data->map->path_north == NULL)
		error = ERROR_NORTH;
	else if (data->map->path_south == NULL)
		error = ERROR_SOUTH;
	else if (data->map->path_west == NULL)
		error = ERROR_WEST;
	else if (data->map->floor_color == NULL)
		error = ERROR_FLOOR;
	else if (data->map->ceiling_color == NULL)
		error = ERROR_CEILING;
	if (error != ERROR_NO)
		print_wrong_textures(data, error);
}

void	check_for_mutiple_textures(t_data *data)
{
	t_error	error;

	error = ERROR_NO;
	if (data->map->path_east_counter > 1)
		error = ERROR_EAST_MULTIPLE;
	else if (data->map->path_north_counter > 1)
		error = ERROR_NORTH_MULTIPLE;
	else if (data->map->path_south_counter > 1)
		error = ERROR_SOUTH_MULTIPLE;
	else if (data->map->path_west_counter > 1)
		error = ERROR_WEST_MULTIPLE;
	else if (data->map->floor_color_counter > 1)
		error = ERROR_FLOOR_MULTIPLE;
	else if (data->map->ceiling_color_counter > 1)
		error = ERROR_CEILING_MULTIPLE;
	if (error != ERROR_NO)
		print_multiple_textures(data, error);
}

void	compare_textures_utils(t_tex_list *tmp, t_data *data)
{
	if (ft_strncmp("WE", tmp->content, 2) == 0)
	{
		data->map->path_west = get_string_path(tmp->content, data);
		data->map->path_west_counter++;
	}
	else if (ft_strncmp("F", tmp->content, 1) == 0)
	{
		data->map->floor_color = get_string_path(tmp->content, data);
		data->map->floor_color_counter++;
	}
	else if (ft_strncmp("C", tmp->content, 1) == 0)
	{
		data->map->ceiling_color = get_string_path(tmp->content, data);
		data->map->ceiling_color_counter++;
	}
}

void	compare_textures(t_data *data)
{
	t_tex_list	*tmp;

	tmp = data->t_list;
	while (tmp)
	{
		if (ft_strncmp("NO", tmp->content, 2) == 0)
		{
			data->map->path_north = get_string_path(tmp->content, data);
			data->map->path_north_counter++;
		}
		else if (ft_strncmp("SO", tmp->content, 2) == 0)
		{
			data->map->path_south = get_string_path(tmp->content, data);
			data->map->path_south_counter++;
		}
		else if (ft_strncmp("EA", tmp->content, 2) == 0)
		{
			data->map->path_east = get_string_path(tmp->content, data);
			data->map->path_east_counter++;
		}
		compare_textures_utils(tmp, data);
		tmp = tmp->next;
	}
}

void	compare_and_check_textures(t_data *data)
{
	trim_before_and_after(data);
	trim_spaces_textures(data);
	syntax_textures(data);
	compare_textures(data);
	check_for_empty_textures(data);
	check_for_mutiple_textures(data);
	get_color_floor(data);
	get_color_ceiling(data);
}
