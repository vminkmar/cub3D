/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:21:03 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/12 11:30:15 by mgraefen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	t_player	*player;
	mlx_t		*mlx;
	mlx_image_t	*img;

	var = NULL;
	map = NULL;
	tex = NULL;
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	var = malloc(sizeof(t_var));
	if (var == NULL)
	{
		print_error("Allocation of Memory failed");
		exit (1);
	}
	parser(argv, var, map, tex);
	// raycaster();
	return (EXIT_SUCCESS);
}