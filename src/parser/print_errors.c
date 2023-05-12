#include "../../include/cub3d.h"

void	print_error(char *message)
{
	ft_putendl_fd(message, 2);
}

void	print_wrong_textures(t_tex_list *tex, t_data *data, t_error error)
{
	if (error == ERROR_EAST)
		print_error("There is no east texture or you choose the wrong one");
	else if (error == ERROR_NORTH)
		print_error("There is no north texture or you choose the wrong one");
	else if (error == ERROR_SOUTH)
		print_error("There is no south texture or you choose the wrong one");
	else if (error == ERROR_WEST)
		print_error("There is no west texture or you choose the wrong one");
	else if (error == ERROR_FLOOR)
		print_error("There is no floor color or you choose the wrong one");
	else if (error == ERROR_CEILING)
		print_error("There is no ceiling color or you choose the wrong one");
	free_list_textures(&tex);
	free_data(data);
	tex = NULL;
	exit (1);
}

void	print_wrong_color(t_error_color error)
{
	if (error == ERROR_COMMA_CEILING)
		print_error("Check the number of commas in ceiling color");
	if (error == ERROR_COMMA_FLOOR)
		print_error("Check the number of commas in floor color");
	if (error == ERROR_NUMBER_FLOOR)
		print_error("Check the amount of numbers in floor color");
	if (error == ERROR_NUMBER_CEILING)
		print_error("Check the amount of numbers in ceiling color");
	if (error == ERROR_ALPHA_FLOOR)
		print_error("Check the for Letters in floor color");
	if (error == ERROR_ALPHA_CEILING)
		print_error("Check for Letters in floor ceiling");
	// free
	exit (1);
}
