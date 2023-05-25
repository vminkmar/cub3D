/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:45 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:28:46 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	create_linked_list_for_textures(t_data **data)
{
	(*data)->t_list = malloc(sizeof(t_tex_list));
	if ((*data)->t_list == NULL)
	{
		print_error("Error\nAllocating Memory failed");
		free_all(*data);
		exit(1);
	}
	(*data)->t_list->next = NULL;
	(*data)->t_list->content = NULL;
}

void	create_linked_list_for_map(t_data **data)
{
	(*data)->m_list = malloc(sizeof(t_map_list));
	if ((*data)->m_list == NULL)
	{
		print_error("Error\nAllocating Memory failed");
		free_all(*data);
		exit(1);
	}
	(*data)->m_list->next = NULL;
	(*data)->m_list->content = NULL;
}

void	add_node_to_map(char *line, t_data **data)
{
	t_map_list	*new_map;

	if ((*data)->m_list->content == NULL)
		(*data)->m_list->content = line;
	else
	{
		new_map = malloc(sizeof(t_map_list));
		if (new_map == NULL)
		{
			print_error("Error\nAllocation of Memory failed");
			free_all(*data);
			exit (1);
		}
		new_map->next = NULL;
		new_map->content = line;
		ft_lstadd_back_map(&(*data)->m_list, new_map);
	}
}

void	add_node_to_tex(char *line, t_data **data)
{
	t_tex_list	*new_tex;

	if ((*data)->t_list->content == NULL)
		(*data)->t_list->content = line;
	else
	{
		new_tex = malloc(sizeof(t_tex_list));
		if (new_tex == NULL)
		{
			print_error("Error\nAllocation of Memory failed");
			free_all(*data);
			exit (1);
		}
		new_tex->next = NULL;
		new_tex->content = line;
		ft_lstadd_back_tex(&(*data)->t_list, new_tex);
	}
}
