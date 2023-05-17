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

void check_syntax_textures(t_tex_list *tex, int issue)
{
	t_error_syntax error;

	if (check_whitespaces(tex->content) == 1)
	{
		error = ERROR_SPACES;
		print_syntax_error(error, issue);
	}
}


void syntax_textures(t_tex_list *tex)
{
	while (tex)
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
		tex = tex->next;
	}
}