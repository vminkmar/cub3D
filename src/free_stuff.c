/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:12:47 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/02 15:10:14 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void free_textures(t_tex_list **tex)
// {
// 	t_tex_list *tmp;

// 	if (tex != NULL)
// 	{
// 		tmp = (*tex);
// 		while(tex)
// 		{
// 			tmp = (*tex);
// 			(*tex) = (*tex)->next;
// 			free(tmp);
// 		}
// 	}
// }

// void free_var(t_var *var)
// {
// 	if (var != NULL)
// 	{
// 		if(var->ceiling_color != NULL)
// 			free(var->ceiling_color);
// 		if(var->floor_color != NULL)
// 			free(var->floor_color);
// 		if(var->path_east != NULL)
// 			free(var->path_east);
// 		if(var->path_north != NULL)
// 			free(var->path_north);
// 		if(var->path_west != NULL)
// 			free(var->path_west);
// 		if(var->path_south != NULL)
// 			free(var->path_south);
// 		if(var->ceiling_color != NULL)
// 			free(var->ceiling_color);
// 	}
// }