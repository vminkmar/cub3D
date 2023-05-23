#include "cub3d.h"

void print_syntax_error(t_error_syntax error, int issue, t_data *data)
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

int check_whitespaces(char *str)
{
	int	i;

	i = 0;
	while(str[i] >= 'A' && str[i] <+ 'Z')
		i++;
	if (ft_charcmp(str[i], WHITESPACES_LESS) == 1
		|| ft_charcmp(str[i + 1], WHITESPACES_LESS))
		return (1);
	return (0);
}

int check_after_name(char *str, int issue)
{
	int i;

	i = 0;
	if (issue < 5)
	{
		if (str[2] != ' ')
			return (1);
	}
	else if (issue >= 5)
	{
		if (str[1] != ' ')
			return (1);
	}
	return (0);

}

void check_syntax_textures(char *str, t_data *data, int issue)
{
	t_error_syntax error;

	error = NO_ERROR;
	if (check_whitespaces(str) == 1)
		error = ERROR_SPACES;
	if (check_after_name(str, issue) == 1)
		error = ERROR_SYNTAX;
	if (error != NO_ERROR)
		print_syntax_error(error, issue, data);
}


void syntax_textures_util(t_tex_list *tmp, t_data *data)
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

int check_for_letters(char *str)
{
	int i;

	i = 0;
	if (str[i + 1] > 'Z' || str[i + 1] < 'A')
		return (1);
	return (0);
}

void print_error_for_syntax(t_data *data, t_error_syntax error)
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

int check_for_letters_after_name(char *str)
{
	if (str[1] != ' ')
		return (1);
	return (0);
}

void syntax_number_of_letters(t_tex_list *tmp, t_data *data)
{
	t_error_syntax error;

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
	else if (ft_strncmp("S", tmp->content, 1) == 0)
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
	if (error != NO_ERROR_SYNTAX)
		print_error_for_syntax(data, error);

}

void syntax_textures(t_data *data)
{
	t_tex_list *tmp;

	tmp = data->t_list;
	while (tmp)
	{
		syntax_textures_util(tmp, data);
		syntax_number_of_letters(tmp, data);
		tmp = tmp->next;
	}
}