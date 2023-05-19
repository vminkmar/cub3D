#include "../../include/cub3d.h"

int	rgb_to_uint(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

void	check_numbers(int red, int green, int blue)
{
	if (red > 255 || red < 0 || blue > 255 || blue < 0 || green > 255
		|| green < 0)
	{
		print_error("Error\nWrong RGB color the numbers have to be 0-255");
		// free
		exit (1);
	}
}

void	 get_color_floor(t_data *data)
{
	char	**numbers_floor;
	int		i;
	int		red;
	int		green;
	int		blue;

	i = 0;
	numbers_floor = ft_split((const char *)data->map->floor_color, ',');
	while (numbers_floor[i] != NULL)
	{
		check_for_spaces(numbers_floor[i], 1);
		if (i == 0)
			red = ft_atoi(numbers_floor[i]);
		if (i == 1)
			green = ft_atoi(numbers_floor[i]);
		if (i == 2)
			blue = ft_atoi(numbers_floor[i]);
		i ++;
	}
	check_colors(data, i, 1, numbers_floor);
	check_numbers(red, green, blue);
	free_numbers(numbers_floor);
	data->map->color_floor = rgb_to_uint(red, green, blue, 255);
}

void	get_color_ceiling(t_data *data)
{
	char	**numbers_ceiling;
	int		i;
	int		red;
	int		green;
	int		blue;

	i = 0;
	numbers_ceiling = ft_split((const char *)data->map->ceiling_color, ',');
	while (numbers_ceiling[i] != NULL)
	{
		check_for_spaces(numbers_ceiling[i], 2);
		if (i == 0)
			red = ft_atoi(numbers_ceiling[i]);
		if (i == 1)
			green = ft_atoi(numbers_ceiling[i]);
		if (i == 2)
			blue = ft_atoi(numbers_ceiling[i]);
		i ++;
	}
	check_colors(data, i, 2, numbers_ceiling);
	check_numbers(red, green, blue);
	free_numbers(numbers_ceiling);
	data->map->color_ceiling = rgb_to_uint(red, green, blue, 255);
}

int check_for_whitespaces(char **colors, char *whitespaces)
{
	int	inner;
	int outer;
	int	spaces;
	int flag;

	flag = 0;
	spaces = 0;
	outer = 0;
	while(colors[outer] != NULL)
	{
		inner = 0;
		flag = 0;
		while(colors[outer][inner] != '\0')
		{
			if ((colors[outer][inner] >= '0' && colors[outer][inner] <= '9') && flag == 1)
				return (1);
			if (colors[outer][inner] < '0' || colors[outer][inner] > '9')
				flag = 1;
			spaces = 0;
			while(whitespaces[spaces] != '\0')
			{
				if (colors[outer][inner] == whitespaces[spaces])
					return (1);
				spaces++;
			}
			inner ++;
		}
		outer++;
	}
	return (0);
}

void	check_colors(t_data *data, int i, int issue, char **colors)
{
	t_error_color	error;

	error = NO_COLOR_ERROR;
	if (i != 3 && issue == 1)
		error = ERROR_COMMA_FLOOR;
	else if (i != 3 && issue == 1)
		error = ERROR_COMMA_CEILING;
	else if (check_for_whitespaces(colors, WHITESPACES_LESS) == 1 && issue == 1)
		error = ERROR_WHITESPACES_FLOOR;
	else if (check_for_whitespaces(colors, WHITESPACES_LESS) == 1 && issue == 2)
		error = ERROR_WHITESPACES_CEILING;
	else if (number_counter(data->map->ceiling_color) == 1)
		error = ERROR_NUMBER_CEILING;
	else if (number_counter(data->map->floor_color) == 1)
		error = ERROR_NUMBER_FLOOR;
	else if (check_for_alpha(data->map->ceiling_color) == 1)
		error = ERROR_ALPHA_CEILING;
	else if (check_for_alpha(data->map->floor_color) == 1)
		error = ERROR_ALPHA_FLOOR;
	if (error != NO_COLOR_ERROR)
		print_wrong_color(error);
}
