#include "../include/cub3d.h"


void init_data(t_data *data)
{	
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
    if (!data->mlx)
		exit(EXIT_FAILURE);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
}

void	ft_free2d(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	if (s)
		free(s);
}

void free_exit(t_data *data)
{
	free(data->player);
	mlx_delete_texture(data->map->tex_door);
	mlx_delete_texture(data->map->tex_north);
	mlx_delete_texture(data->map->tex_south);
	mlx_delete_texture(data->map->tex_west);
	mlx_delete_texture(data->map->tex_east);
	free(data->map->path_north);
	free(data->map->path_south);
	free(data->map->path_west);
	free(data->map->path_east);
	free(data->map->floor_color);
	free(data->map->ceiling_color);
	ft_free2d(data->map->map);
	free(data->map);
	mlx_terminate(data->mlx);
	free(data);
}

int main2(int argc, char **argv)
{
	t_data		*data;

	data = NULL;
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		print_error("Allocation of Memory failed");
		exit (1);
	}
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(EXIT_FAILURE);
	data->map = malloc(sizeof(t_map));
	parser(argv, data);
	init_data(data);
	init_player(data);
	data->map->map[(int)data->player->p_start.y][(int)data->player->p_start.x] = WALKABLE;
    mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	raycaster(data);
	free_exit(data);
	return (EXIT_SUCCESS);
}

int main(int argc, char ** argv)
{
	main2(argc, argv);
	system("leaks cub3D");
}