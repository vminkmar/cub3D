#include "cub3d.h"

void print_syntax_error(t_error_syntax error, int issue)
{
	if (issue == 1 && error == ERROR_SPACES)
		print_error("Error\nUpper cases in south texture");
	if (issue == 2 && error == ERROR_SPACES)
		print_error("Error\nUpper cases in east texture");
	if (issue == 3 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in east texture");
	if (issue == 4 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in west texture");
	if (issue == 5 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in floor color");
	if (issue == 6 && error == ERROR_SPACES)
		print_error("Error\nNot allowed whitespaces in ceiling color");
	// free
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

void check_syntax_textures(t_tex_list *tex, int issue)
{
	t_error_syntax error;

	error = NO_ERROR;
	if (check_whitespaces(tex->content) == 1)
		error = ERROR_SPACES;
	if (check_after_name(tex->content, issue) == 1)
		error = ERROR_SYNTAX;
	if (error != NO_ERROR)
		print_syntax_error(error, issue);
}


void syntax_textures_util(t_tex_list *tex)
{
	if (ft_strncmp("NO", tex->content, 2) == 0)
		check_syntax_textures(tex, 1);
	else if (ft_strncmp("SO", tex->content, 2) == 0)
		check_syntax_textures(tex, 2);
	else if (ft_strncmp("EA", tex->content, 2) == 0)
		check_syntax_textures(tex, 3);
	else if (ft_strncmp("WE", tex->content, 2) == 0)
		check_syntax_textures(tex, 4);
	else if (ft_strncmp("F", tex->content, 1) == 0)
		check_syntax_textures(tex, 5);
	else if (ft_strncmp("C", tex->content, 1) == 0)
		check_syntax_textures(tex, 6);
}

int check_for_letters(char *str)
{
	int i;

	i = 0;
	if (str[i + 1] > 'Z' || str[i + 1] < 'A')
		return (1);
	return (0);
}

void print_error_for_syntax(t_tex_list *tex, t_error_syntax error)
{
	if (error == ERROR_SYNTAX_SOUTH)
		print_error("Error\nThere is a syntax error in the south texture");
	else if (error == ERROR_SYNTAX_WEST)
		print_error("Error\nThere is a syntax error in the west texture");
	else if (error == ERROR_SYNTAX_NORTH)
		print_error("Error\nThere is a syntax error in the north texture");
	else if (error == ERROR_SYNTAX_EAST)
		print_error("Error\nThere is a syntax error in the east texture");
	// free
	tex = NULL; //!!!!!!
	exit (1);
}


void syntax_number_of_letters(t_tex_list *tex)
{
	t_error_syntax error;

	error = NO_ERROR_SYNTAX;
	if (ft_strncmp("N", tex->content, 1) == 0)
	{
		if (check_for_letters(tex->content) == 1)
			error = ERROR_SYNTAX_NORTH;
	}
	else if (ft_strncmp("E", tex->content, 1) == 0)
	{
		if (check_for_letters(tex->content) == 1)
			error = ERROR_SYNTAX_EAST;
	}	
	else if (ft_strncmp("W", tex->content, 1) == 0)
	{
		if (check_for_letters(tex->content) == 1)
			error = ERROR_SYNTAX_WEST;
	}	
	else if (ft_strncmp("S", tex->content, 1) == 0)
	{
		if (check_for_letters(tex->content) == 1)
			error = ERROR_SYNTAX_SOUTH;
	}
	if (error != NO_ERROR_SYNTAX)
		print_error_for_syntax(tex, error);

}

void syntax_textures(t_tex_list *tex)
{
	while (tex)
	{
		syntax_textures_util(tex);
		syntax_number_of_letters(tex);
		tex = tex->next;
	}
}