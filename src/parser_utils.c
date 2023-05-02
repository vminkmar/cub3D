/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:02:44 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/02 10:51:35 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strcmp(char *first, char *second)
{
	int i;

	i = 0;
	while(first[i] != '\0' && second[i] != '\0')
	{
		if(first[i] != second[i])
			return (1);
		i ++;
	}
	return (0);
}

void create_linked_list_for_textures(t_tex_list **tex)
{
	*tex = malloc(sizeof(t_tex_list));
	if (*tex == NULL)
	{
		print_error("Allocating Memory failed");
		exit(1);
	}
	(*tex)->next = NULL;
	(*tex)->content = NULL;
}

void create_linked_list_for_map(t_map_list **map)
{
	*map = malloc(sizeof(t_map_list));
	if (*map == NULL)
	{
		print_error("Allocating Memory failed");
		exit(1);
	}
	(*map)->next = NULL;
	(*map)->content = NULL;
	
}

