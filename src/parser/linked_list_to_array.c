/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:39 by vminkmar          #+#    #+#             */
/*   Updated: 2023/06/01 10:37:05 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_start_point(t_data *data, char c, int line, int character)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->player->p_start.y = line + 0.5;
		data->player->p_start.x = character + 0.5;
		if (c == 'N')
			data->player->angle = 270;
		if (c == 'S')
			data->player->angle = 90;
		if (c == 'E')
			data->player->angle = 0;
		if (c == 'W')
			data->player->angle = 180;
		data->player->counter_p_start ++;
	}	
}

void	check_for_startpoint(t_data *data)
{
	if (data->player->counter_p_start < 1)
	{
		print_error("There is no start point on the map");
		free_all(data);
		exit(1);
	}
	if (data->player->counter_p_start > 1)
	{
		print_error("There are too many startpoints on the map");
		free_all(data);
		exit(1);
	}
}

char	*get_map_types(const char *s1, int line, t_data *data)
{
	char	*new;
	size_t	character;

	new = malloc(sizeof(t_type *) * (ft_strlen(s1) + 1));
	if (new == NULL)
		return (NULL);
	character = 0;
	while (character < ft_strlen(s1) + 1)
	{	
		get_start_point(data, s1[character], line, character);
		if (s1[character] == '1')
			new[character] = WALL;
		else if (s1[character] == '0' || s1[character] == 'N'
			|| s1[character] == 'S' || s1[character] == 'W'
			|| s1[character] == 'E')
			new[character] = WALKABLE;
		else if (s1[character] == 'D')
			new[character] = CLOSED_DOOR;
		else
			new[character] = OTHERS;
		character++;
	}
	new[character] = '\0';
	return (new);
}

void	get_max_width(char *str, t_data *data)
{
	int	length;

	length = ft_strlen(str);
	if (length > data->map->max_width)
		data->map->max_width = length;
}

void	transfer_map_to_array(t_data *data)
{
	int			line;
	t_map_list	*tmp;

	tmp = data->m_list;
	line = 0;
	data->map->map = malloc(sizeof(t_type *) *(data->map->max_height + 1));
	while (tmp)
	{
		if (check_if_allowed_character(tmp->content) == 1)
		{
			print_error("Error\nNot allowed character in Map");
			data->map->map[line] = NULL;
			free_all(data);
			exit (1);
		}
		data->map->map[line] = get_map_types(tmp->content, line, data);
		get_max_width(data->map->map[line], data);
		line ++;
		tmp = tmp->next;
	}
	data->map->map[line] = NULL;
	check_for_startpoint(data);
}
