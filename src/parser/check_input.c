#include "../../include/cub3d.h"

int	check_input(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Check the number of Arguments!");
		return (1);
	}
	if (ft_strncmp("maps/", argv[1], 5) != 0)
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
