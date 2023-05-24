#include "../../include/cub3d.h"

void	get_color_floor(t_data *data)
{
	char	**numbers_floor;
	char	**colors_new;

	colors_new = malloc(sizeof(char *) * (4));
	numbers_floor = ft_split((const char *)data->map->floor_color, ',');
	check_the_array(numbers_floor, colors_new, data);
	check_for_spaces(numbers_floor[0], 1, data);
	check_for_spaces(numbers_floor[1], 1, data);
	check_for_spaces(numbers_floor[2], 1, data);
	colors_new[0] = ft_strtrim(numbers_floor[0], " ");
	data->map->red = ft_atoi(colors_new[0]);
	colors_new[1] = ft_strtrim(numbers_floor[1], " ");
	data->map->green = ft_atoi(colors_new[1]);
	colors_new[2] = ft_strtrim(numbers_floor[2], " ");
	data->map->blue = ft_atoi(colors_new[2]);
	colors_new[3] = NULL;
	free_numbers(numbers_floor);
	check_colors(data, 1, colors_new);
	check_numbers(data, colors_new);
	free_numbers(colors_new);
	data->map->color_floor = rgb_to_uint(data->map->red, data->map->green,
			data->map->blue, 255);
}

void	get_color_ceiling(t_data *data)
{
	char	**numbers_floor;
	char	**colors_new;

	colors_new = malloc(sizeof(char *) * (4));
	numbers_floor = ft_split((const char *)data->map->ceiling_color, ',');
	check_the_array(numbers_floor, colors_new, data);
	check_for_spaces(numbers_floor[0], 1, data);
	check_for_spaces(numbers_floor[1], 1, data);
	check_for_spaces(numbers_floor[2], 1, data);
	colors_new[0] = ft_strtrim(numbers_floor[0], " ");
	data->map->red = ft_atoi(colors_new[0]);
	colors_new[1] = ft_strtrim(numbers_floor[1], " ");
	data->map->green = ft_atoi(colors_new[1]);
	colors_new[2] = ft_strtrim(numbers_floor[2], " ");
	data->map->blue = ft_atoi(colors_new[2]);
	colors_new[3] = NULL;
	free_numbers(numbers_floor);
	check_colors(data, 2, colors_new);
	check_numbers(data, colors_new);
	free_numbers(colors_new);
	data->map->color_floor = rgb_to_uint(data->map->red, data->map->green,
			data->map->blue, 255);
}

int	check_for_whitesapces_utils(char **colors, char *whitespaces, int outer)
{
	int	spaces;
	int	flag;
	int	inner;

	flag = 0;
	spaces = 0;
	inner = 0;
	while (colors[outer] && colors[outer][inner] != '\0')
	{
		if ((colors[outer][inner] >= '0' && colors[outer][inner] <= '9')
			&& flag == 1)
			return (1);
		if (ft_isdigit(colors[outer][inner]) == 0
			&& colors[outer][inner] != '-')
			flag = 1;
		spaces = 0;
		while (whitespaces && whitespaces[spaces] != '\0')
		{
			if (colors[outer][inner] == whitespaces[spaces])
				return (1);
			spaces++;
		}
		inner ++;
	}
	return (0);
}

int	check_for_whitespaces(char **colors, char *whitespaces)
{
	int	outer;

	outer = 0;
	while (colors[outer] != NULL)
	{
		if (check_for_whitesapces_utils(colors, whitespaces, outer) == 1)
			return (1);
		outer++;
	}
	return (0);
}

void	check_colors(t_data *data, int issue, char **colors)
{
	t_error_color	error;

	error = NO_COLOR_ERROR;
	if (check_for_commas(data->map->ceiling_color) == 1)
		error = ERROR_COMMA_CEILING;
	else if (check_for_commas(data->map->floor_color) == 1)
		error = ERROR_COMMA_FLOOR;
	else if (number_counter(colors) == 1)
		error = ERROR_NUMBER_CEILING;
	else if (number_counter(colors) == 1)
		error = ERROR_NUMBER_FLOOR;
	else if (check_for_alpha(colors) == 1 && issue == 2)
		error = ERROR_ALPHA_CEILING;
	else if (check_for_alpha(colors) == 1 && issue == 1)
		error = ERROR_ALPHA_FLOOR;
	else if (check_for_whitespaces(colors, WHITESPACES_LESS) == 1 && issue == 1)
		error = ERROR_WHITESPACES_FLOOR;
	else if (check_for_whitespaces(colors, WHITESPACES_LESS) == 1 && issue == 2)
		error = ERROR_WHITESPACES_CEILING;
	if (error != NO_COLOR_ERROR)
		print_wrong_color(error, data, colors);
}
