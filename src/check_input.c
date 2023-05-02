/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:45:11 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/02 10:24:18 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_error(char *message)
{
	ft_putendl_fd(message, 2);
}

int check_input(int argc, char **argv)
{
	if(argc != 2)
	{
		print_error("Check the number of Arguments!");
		return (1);
	}
	if(ft_strncmp("maps/", argv[1], 5) != 0)
	{
		print_error("You chose the wrong directory");
		return (1);
	}
	if (ft_strncmp(argv[1], "", 1) == 0)
	{
		print_error("You forgot the Path!");
		return (1);
	}
	return (0);
}