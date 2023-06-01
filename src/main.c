/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:29:07 by vminkmar          #+#    #+#             */
/*   Updated: 2023/06/01 10:44:42 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_data *data)
{
	data->player->fov = FIELD_OF_VIEW;
	data->map->map[(int)data->player->p_start.y][(int)data->player->p_start.x]
		= WALKABLE;
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
}

void	init_data(t_data *data)
{	
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->minimap_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	data->framecount = 0;
}

void	init_map(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (free(data->player), free(data), (void)EXIT_FAILURE);
	data->map->tex_door = malloc(sizeof(mlx_texture_t *) * 2);
	if (!data->map->tex_door)
		return (free(data->map), free(data->player), free(data),
			(void)EXIT_FAILURE);
}

t_data	*pre_parser_init(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
	{
		print_error("Allocation of Data Memory failed");
		return (exit(1), NULL);
	}
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		print_error("Allocation of Player Memory failed");
		free(data);
		return (exit(1), NULL);
	}
	return (data);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	data = NULL;
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	data = pre_parser_init(data);
	init_map(data);
	parser(argv, data);
	init_data(data);
	init_player(data);
	raycaster(data);
	free_exit(data);
	return (EXIT_SUCCESS);
}
