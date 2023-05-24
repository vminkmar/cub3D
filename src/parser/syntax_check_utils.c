#include "cub3d.h"

int	check_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] >= 'A' && str[i] <= 'Z')
		i++;
	if (ft_charcmp(str[i], WHITESPACES_LESS) == 1
		|| ft_charcmp(str[i + 1], WHITESPACES_LESS))
		return (1);
	return (0);
}

int	check_after_name(char *str, int issue)
{
	int	i;

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

int	check_for_letters(char *str)
{
	int	i;

	i = 0;
	if (str[i + 1] > 'Z' || str[i + 1] < 'A')
		return (1);
	return (0);
}

void	check_syntax_textures(char *str, t_data *data, int issue)
{
	t_error_syntax	error;

	error = NO_ERROR;
	if (check_whitespaces(str) == 1)
		error = ERROR_SPACES;
	if (check_after_name(str, issue) == 1)
		error = ERROR_SYNTAX;
	if (error != NO_ERROR)
		print_syntax_error(error, issue, data);
}

int	check_for_letters_after_name(char *str)
{
	if (str[1] != ' ')
		return (1);
	return (0);
}
