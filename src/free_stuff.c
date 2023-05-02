/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:12:47 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/02 11:19:46 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_textures(t_tex_list **tex)
{
	t_tex_list *tmp;

	if (tex != NULL)
	{
		tmp = (*tex);
		while(tex)
		{
			tmp = (*tex);
			(*tex) = (*tex)->next;
			free(tmp);
		}
	}
}