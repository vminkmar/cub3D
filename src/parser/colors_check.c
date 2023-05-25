/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:12 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:28:13 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_the_array(char **numbers_floor, char **colors_new, t_data *data)
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

int	check_array_length(char **str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != NULL)
		i++;
	if (i != 3)
		return (1);
	return (0);
}
