#include "cub3d.h"

int main(int argc, char **argv)
{
	t_var			*var;
	t_tex_list		*tex;
	t_map_list		*map;

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