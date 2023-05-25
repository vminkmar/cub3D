/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linekd_list_to_array_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:36 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:30:56 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_allowed_character(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'D' || str[i] == 'E'
			|| str[i] == 'S' || str[i] == '1' || str[i] == '0' || str[i] == ' '
			|| str[i] == '\n')
			i++;
		else
			return (1);
	}
	return (0);
}
