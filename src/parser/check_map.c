#include "../../include/cub3d.h"

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

void	check_around_zero(char **map, int line, int character, t_data *data)
{
	t_error	error;

	error = ERROR_NO;
	if (map[0][character] == WALKABLE || map[line][0] == WALKABLE
		|| map[data->map->max_height - 1][character] == WALKABLE
		|| map[line][ft_strlen(map[line]) - 1] == WALKABLE)
		error = ERROR_INVALID;
	else if (map[line][character - 1] == OTHERS)
		error = ERROR_INVALID;
	else if (map[line][character + 1] == OTHERS)
		error = ERROR_INVALID;
	else if (map[line - 1][character] == OTHERS)
		error = ERROR_INVALID;
	else if (map[line + 1][character] == OTHERS)
		error = ERROR_INVALID;
	if (error == ERROR_INVALID)
	{
		print_error("Error\nMap is not surrounded by walls");
		free_all(data);
		exit (1);
	}
}

void	check_around_door(char **map, int line, int character, t_data *data)
{
	t_error	error;

	error = ERROR_NO;
	if (map[0][character] == CLOSED_DOOR || map[line][0] == CLOSED_DOOR
		|| map[data->map->max_height - 1][character] == CLOSED_DOOR
		|| map[line][ft_strlen(map[line]) - 1] == CLOSED_DOOR)
		error = ERROR_INVALID_DOOR;
	else if (map[line][character - 1] == OTHERS)
		error = ERROR_INVALID_DOOR;
	else if (map[line][character + 1] == OTHERS)
		error = ERROR_INVALID_DOOR;
	else if (map[line - 1][character] == OTHERS)
		error = ERROR_INVALID_DOOR;
	else if (map[line + 1][character] == OTHERS)
		error = ERROR_INVALID_DOOR;
	if (error == ERROR_INVALID_DOOR)
	{
		print_error("Error\nCheck that doors are not in the outside wall");
		free_all(data);
		exit (1);
	}
}

void	check_map(char **map, t_data *data)
{
	int	line;
	int	character;

	line = 0;
	while (map[line] != NULL)
	{
		character = 0;
		while (map[line][character] != '\0')
		{	
			if (map[line][character] == WALKABLE)
				check_around_zero(map, line, character, data);
			if (map[line][character] == CLOSED_DOOR)
				check_around_door(map, line, character, data);
			if (ft_whitespaces(map[line][character]) == 1)
			{
				print_error("Error\nInvalid whitespace in map");
				free_all(data);
				exit (1);
			}
			character ++;
		}
		line ++;
	}
}
