#include "../../include/cub3d.h"

int	rgb_to_uint(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

void	check_numbers(t_data *data, char **colors)
{
	if (data->map->red > 255 || data->map->red < 0 || data->map->blue > 255
		|| data->map->blue < 0 || data->map->green > 255
		|| data->map->green < 0)
	{
		print_error("Error\nWrong RGB color the numbers have to be 0-255");
		free_numbers(colors);
		free_all(data);
		exit (1);
	}
}

void check_the_array(char **numbers_floor, char **colors_new, t_data *data)
{
	if (check_array_length(numbers_floor) == 1)
	{
		print_error("You forgot a number or a comma in the ceiling texture");
		free_numbers(numbers_floor);
		free(colors_new);
		free_all(data);
		exit (1);
	}
}

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
	data->map->color_floor = rgb_to_uint(data->map->red, data->map->green, data->map->blue, 255);
}

int check_array_length(char **str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(str[i] != NULL)
		i++;
	if (i != 3)
		return (1);
	return (0);
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
	data->map->color_floor = rgb_to_uint(data->map->red, data->map->green, data->map->blue, 255);
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
		while(colors[outer] && colors[outer][inner] != '\0')
		{
			if ((colors[outer][inner] >= '0' && colors[outer][inner] <= '9') && flag == 1)
				return (1);
			if (ft_isdigit(colors[outer][inner]) == 0 && colors[outer][inner] != '-')
				flag = 1;
			spaces = 0;
			while(whitespaces && whitespaces[spaces] != '\0')
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
