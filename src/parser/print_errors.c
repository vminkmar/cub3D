#include "../../include/cub3d.h"

void	print_wrong_textures(t_data *data, t_error error)
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
	free_all(data);
	exit (1);
}

void	print_multiple_textures(t_data *data, t_error error)
{
	if (error == ERROR_EAST_MULTIPLE)
		print_error("Error\nThere are too many east texture");
	else if (error == ERROR_NORTH_MULTIPLE)
		print_error("Error\nThere are too many north texture");
	else if (error == ERROR_SOUTH_MULTIPLE)
		print_error("Error\nThere are too many south texture");
	else if (error == ERROR_WEST_MULTIPLE)
		print_error("Error\nThere are too many west texture");
	else if (error == ERROR_FLOOR_MULTIPLE)
		print_error("Error\nThere are too many floor color");
	else if (error == ERROR_CEILING_MULTIPLE)
		print_error("Error\nThere are too many ceiling color");
	free_all(data);
	exit (1);
}

void	print_wrong_color(t_error_color error, t_data *data, char **colors)
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
	free_numbers(colors);
	free_all(data);
	exit (1);
}

void	print_syntax_error(t_error_syntax error, int issue, t_data *data)
{
	if (issue == 1 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in north texture");
	else if (issue == 2 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in south texture");
	else if (issue == 3 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in east texture");
	else if (issue == 4 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in west texture");
	else if (issue == 5 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in floor color");
	else if (issue == 6 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in ceiling color");
	else if (issue == 1 && error == ERROR_SYNTAX)
		print_error("Error\nCheck the syntax in north texture");
	else if (issue == 2 && error == ERROR_SYNTAX)
		print_error("Error\nCheck the syntax in south texture");
	else if (issue == 3 && error == ERROR_SYNTAX)
		print_error("Error\nCheck the syntax in east texture");
	else if (issue == 4 && error == ERROR_SYNTAX)
		print_error("Error\nCheck the syntax in west texture");
	else if (issue == 5 && error == ERROR_SYNTAX)
		print_error("Error\nCheck the syntax in floor color");
	else if (issue == 6 && error == ERROR_SYNTAX)
		print_error("Error\nCheck the syntax in ceiling color");
	free_all(data);
	exit (1);
}
