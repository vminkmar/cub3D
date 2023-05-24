#include "cub3d.h"

void	syntax_textures_util(t_tex_list *tmp, t_data *data)
{
	if (ft_strncmp("NO", tmp->content, 2) == 0)
		check_syntax_textures(tmp->content, data, 1);
	else if (ft_strncmp("SO", tmp->content, 2) == 0)
		check_syntax_textures(tmp->content, data, 2);
	else if (ft_strncmp("EA", tmp->content, 2) == 0)
		check_syntax_textures(tmp->content, data, 3);
	else if (ft_strncmp("WE", tmp->content, 2) == 0)
		check_syntax_textures(tmp->content, data, 4);
	else if (ft_strncmp("F", tmp->content, 1) == 0)
		check_syntax_textures(tmp->content, data, 5);
	else if (ft_strncmp("C", tmp->content, 1) == 0)
		check_syntax_textures(tmp->content, data, 6);
}

void	print_error_for_syntax(t_data *data, t_error_syntax error)
{
	if (error == ERROR_SYNTAX_SOUTH)
		print_error("Error\nThere is a syntax error in the south texture");
	else if (error == ERROR_SYNTAX_WEST)
		print_error("Error\nThere is a syntax error in the west texture");
	else if (error == ERROR_SYNTAX_NORTH)
		print_error("Error\nThere is a syntax error in the north texture");
	else if (error == ERROR_SYNTAX_EAST)
		print_error("Error\nThere is a syntax error in the east texture");
	else if (error == ERROR_SYNTAX_FLOOR)
		print_error("Error\nThere is a syntax error in the floor texture");
	else if (error == ERROR_SYNTAX_CEILING)
		print_error("Error\nThere is a syntax error in the ceiling texture");
	free_all(data);
	exit (1);
}

int	syntax_number_of_letters_utils(t_tex_list *tmp, int error)
{
	if (ft_strncmp("S", tmp->content, 1) == 0)
	{
		if (check_for_letters(tmp->content) == 1)
			error = ERROR_SYNTAX_SOUTH;
	}
	else if (ft_strncmp("F", tmp->content, 1) == 0)
	{
		if (check_for_letters_after_name(tmp->content) == 1)
			error = ERROR_SYNTAX_FLOOR;
	}
	else if (ft_strncmp("C", tmp->content, 1) == 0)
	{
		if (check_for_letters_after_name(tmp->content) == 1)
			error = ERROR_SYNTAX_CEILING;
	}
	return (error);
}

void	syntax_number_of_letters(t_tex_list *tmp, t_data *data)
{
	t_error_syntax	error;

	error = NO_ERROR_SYNTAX;
	if (ft_strncmp("N", tmp->content, 1) == 0)
	{
		if (check_for_letters(tmp->content) == 1)
			error = ERROR_SYNTAX_NORTH;
	}
	else if (ft_strncmp("E", tmp->content, 1) == 0)
	{
		if (check_for_letters(tmp->content) == 1)
			error = ERROR_SYNTAX_EAST;
	}	
	else if (ft_strncmp("W", tmp->content, 1) == 0)
	{
		if (check_for_letters(tmp->content) == 1)
			error = ERROR_SYNTAX_WEST;
	}	
	error = syntax_number_of_letters_utils(tmp, error);
	if (error != NO_ERROR_SYNTAX)
		print_error_for_syntax(data, error);
}

void	syntax_textures(t_data *data)
{
	t_tex_list	*tmp;

	tmp = data->t_list;
	while (tmp)
	{
		syntax_textures_util(tmp, data);
		syntax_number_of_letters(tmp, data);
		tmp = tmp->next;
	}
}
