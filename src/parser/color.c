#include "cub3d.h"

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

void	get_color_floor(t_var *var)
{
	char	**numbers_floor;
	int		i;
	int		red;
	int		green;
	int		blue;

	i = 0;
	numbers_floor = ft_split((const char *)var->floor_color, ',');
	while (numbers_floor[i] != NULL)
	{
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
	var->color_floor = rgb_to_uint(red, green, blue);
}

void	get_color_ceiling(t_var *var)
{
	char	**numbers_ceiling;
	int		i;
	int		red;
	int		green;
	int		blue;

	i = 0;
	numbers_ceiling = ft_split((const char *)var->ceiling_color, ',');
	while (numbers_ceiling[i] != NULL)
	{
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
	var->color_ceiling = rgb_to_uint(red, green, blue);
}

void	check_colors(t_var *var)
{
	t_error_color	error;

	error = NO_ERROR;
	if (check_for_commas(var->floor_color) == 1)
		error = ERROR_COMMA_FLOOR;
	else if (check_for_commas(var->ceiling_color) == 1)
		error = ERROR_COMMA_CEILING;
	else if (number_counter(var->ceiling_color) == 1)
		error = ERROR_NUMBER_CEILING;
	else if (number_counter(var->floor_color) == 1)
		error = ERROR_NUMBER_FLOOR;
	else if (check_for_alpha(var->ceiling_color) == 1)
		error = ERROR_ALPHA_CEILING;
	else if (check_for_alpha(var->floor_color) == 1)
		error = ERROR_ALPHA_FLOOR;
	if (error != NO_ERROR)
		print_wrong_color(error);
}
