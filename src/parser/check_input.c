/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:02 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:28:03 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_input(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Error\nCheck the number of Arguments!");
		return (1);
	}
	if (ft_strncmp(argv[1], "", 1) == 0)
	{
		print_error("Error\nYou forgot the Path!");
		return (1);
	}
	return (0);
}
