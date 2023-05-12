#include "../../include/cub3d.h"

uint32_t	rgb_to_uint(int red, int green, int blue)
{
	uint32_t	result;

	result = 0;
	result |= (uint32_t)red << 16;
	result |= (uint32_t)green << 8;
	result |= (uint32_t)blue;
	return (result);
}

void	check_numbers(int red, int green, int blue)
{
	if (red > 256 || red < 0 || blue > 256 || blue < 0 || green > 256
		|| green < 0)
	{
		print_error("Wrong RGB color");
		// free
		exit (1);
	}
}

void	get_color_floor(t_data *data)
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
	check_numbers(red, green, blue);
	free_numbers(numbers_floor);
	data->map->color_floor = rgb_to_uint(red, green, blue);
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
	check_numbers(red, green, blue);
	free_numbers(numbers_ceiling);
	data->map->color_ceiling = rgb_to_uint(red, green, blue);
}

void	check_colors(t_data *data)
{
	t_error_color	error;

	error = NO_ERROR;
	if (check_for_commas(data->map->floor_color) == 1)
		error = ERROR_COMMA_FLOOR;
	else if (check_for_commas(data->map->ceiling_color) == 1)
		error = ERROR_COMMA_CEILING;
	else if (number_counter(data->map->ceiling_color) == 1)
		error = ERROR_NUMBER_CEILING;
	else if (number_counter(data->map->floor_color) == 1)
		error = ERROR_NUMBER_FLOOR;
	else if (check_for_alpha(data->map->ceiling_color) == 1)
		error = ERROR_ALPHA_CEILING;
	else if (check_for_alpha(data->map->floor_color) == 1)
		error = ERROR_ALPHA_FLOOR;
	if (error != NO_ERROR)
		print_wrong_color(error);
}
