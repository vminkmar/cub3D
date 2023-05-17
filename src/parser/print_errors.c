#include "../../include/cub3d.h"

void	print_error(char *message)
{
	ft_putendl_fd(message, 2);
}

void	print_wrong_textures(t_tex_list *tex, t_data *data, t_error error)
{
	if (error == ERROR_EAST)
		print_error("Error\nThere is no east texture");
	else if (error == ERROR_NORTH)
		print_error("Error\nThere is no north texture");
	else if (error == ERROR_SOUTH)
		print_error("Error\nThere is no south texture");
	else if (error == ERROR_WEST)
		print_error("Error\nThere is no west texture");
	else if (error == ERROR_FLOOR)
		print_error("Error\nThere is no floor color");
	else if (error == ERROR_CEILING)
		print_error("Error\nThere is no ceiling color");
	free_list_textures(&tex);
	free_data(data);
	tex = NULL;
	exit (1);
}

void	print_wrong_color(t_error_color error)
{
	if (error == ERROR_COMMA_CEILING)
		print_error("Error\nCheck the number of commas in ceiling color");
	if (error == ERROR_COMMA_FLOOR)
		print_error("Error\nCheck the number of commas in floor color");
	if (error == ERROR_NUMBER_FLOOR)
		print_error("Error\nCheck the amount of numbers in floor color");
	if (error == ERROR_NUMBER_CEILING)
		print_error("Error\nCheck the amount of numbers in ceiling color");
	if (error == ERROR_ALPHA_FLOOR)
		print_error("Error\nCheck for Letters in floor color");
	if (error == ERROR_ALPHA_CEILING)
		print_error("Error\nCheck for Letters in ceiling color");
	if (error == ERROR_WHITESPACES_FLOOR)
		print_error("Error\nCheck for whitespaces in floor color");
	if (error == ERROR_WHITESPACES_CEILING)
		print_error("Error\nCheck for whitespaces in ceiling color");
	// free
	exit (1);
}
