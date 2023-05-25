/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:20 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:28:21 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_list_textures(t_tex_list **tex)
{
	t_tex_list	*tmp;

	if (tex != NULL)
	{
		tmp = (*tex);
		while ((*tex) != NULL)
		{
			tmp = (*tex);
			(*tex) = (*tex)->next;
			free(tmp->content);
			free(tmp);
		}
	}
	*tex = NULL;
}

void	free_data(t_data *data)
{
	free(data->map->tex_door);
	free(data->map->path_north);
	free(data->map->path_south);
	free(data->map->path_west);
	free(data->map->path_east);
	free(data->map->floor_color);
	free(data->map->ceiling_color);
}

void	free_list_map(t_map_list **map)
{
	t_map_list	*head;
	t_map_list	*tmp;

	head = *map;
	while (head)
	{
		free(head->content);
		tmp = head->next;
		free(head);
		head = tmp;
	}
	*map = NULL;
}

void	free_numbers(char **numbers)
{
	int	i;

	i = 0;
	while (numbers[i] != NULL)
	{
		free(numbers[i]);
		i ++;
	}
	free(numbers);
	numbers = NULL;
}
