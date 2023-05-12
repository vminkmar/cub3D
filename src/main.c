#include "../include/cub3d.h"


void init_data(t_data *data)
{	
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
    if (!data->mlx)
		exit(EXIT_FAILURE);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(EXIT_FAILURE);
	init_player(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
}

int main(int argc, char **argv)
{
	t_data		*data;

	data = NULL;
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	(void) argv;
	(void) argc;
	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		print_error("Allocation of Memory failed");
		exit (1);
	}
	init_data(data);
	parser(argv, data);
	// raycaster(data);
	return (EXIT_SUCCESS);
}