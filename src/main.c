#include "cub3d.h"

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