/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:07 by vminkmar          #+#    #+#             */
/*   Updated: 2023/06/01 10:19:55 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_for_commas(char *str)
{
	int	i;
	int	comma_counter;

	i = 0;
	comma_counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			comma_counter++;
		if (str[i] == ',' && str[i + 1] == ',')
			return (1);
		i ++;
	}
	if (comma_counter != 2)
		return (1);
	return (0);
}

int	number_counter(char **str)
{
	int	inner;
	int	outer;
	int	counter;

	counter = 0;
	inner = 0;
	outer = 0;
	while (str[outer] != NULL)
	{
		counter ++;
		outer ++;
	}
	if (counter != 3)
		return (1);
	return (0);
}

int	check_for_alpha(char **str)
{
	int	i;
	int	outer;

	outer = 0;
	i = 0;
	while (str[outer] != NULL)
	{
		i = 0;
		while (str[outer][i] != '\0')
		{
			if (str[outer][i] == ',' || str[outer][i] == '\n')
				i ++;
			if (str[outer][i] == '\0')
				break ;
			if (ft_isalpha(str[outer][i]) == 1)
				return (1);
			i ++;
		}
		outer++;
	}
	return (0);
}

int	compare_strings(char *first, char *second)
{
	int	i;
	int	j;

	i = 0;
	if (!first)
	{
		exit(1);
	}
	while (first[i] != '\0')
	{
		j = 0;
		while (second[j] != '\0')
		{
			if (first[i] == second[j])
				return (1);
			j ++;
		}
		i++;
	}
	return (0);
}

void	check_for_spaces(char *str, int flag, t_data *data)
{
	if (compare_strings(str, WHITESPACES_LESS) == 1)
	{
		if (flag == 1)
			print_error("There are whitespaces in the floor color");
		if (flag == 2)
			print_error("There are whitespaces in the ceiling color");
		free_all(data);
		exit (1);
	}
}
