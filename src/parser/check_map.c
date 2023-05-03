#include "cub3d.h"

int	ft_whitespaces(char c)
{
	if (c == '\t' || c == '\r' || c == '\f' || c == '\v' || c == '\n')
		return (1);
	return (0);
}

int	ft_charcmp(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	check_around_zero(char **map, int line, int character, t_var *var)
{
	t_error	error;

	error = ERROR_NO;
	if (map[0][character] == '0' || map[line][0] == '0'
		|| map[var->map.height - 1][character] == '0'
		|| map[line][ft_strlen(map[line]) - 1] == '0')
		error = ERROR_INVALID;
	else if (ft_charcmp(map[line][character - 1], WHITESPACES) == 1)
		error = ERROR_INVALID;
	else if (ft_charcmp(map[line][character + 1], WHITESPACES) == 1)
		error = ERROR_INVALID;
	else if (ft_charcmp(map[line - 1][character], WHITESPACES) == 1)
		error = ERROR_INVALID;
	else if (ft_charcmp(map[line + 1][character], WHITESPACES) == 1)
		error = ERROR_INVALID;
	if (error == ERROR_INVALID)
	{
		print_error("Invalid map");
		// free;
		exit (1);
	}
}

void	check_map(char **map, t_var *var)
{
	int	line;
	int	character;

	line = 0;
	while (map[line] != NULL)
	{
		character = 0;
		while (map[line][character] != '\n' && map[line][character] != '\0')
		{	
			if (map[line][character] == '0')
				check_around_zero(map, line, character, var);
			if (ft_whitespaces(map[line][character]) == 1)
			{
				print_error("There is a not allowed whitespace in the map");
				// free
				exit (1);
			}
			character ++;
		}
		line ++;
	}
}
