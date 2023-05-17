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
		if (comma_counter > 2)
			return (1);
		i ++;
	}
	return (0);
}

int	number_counter(char *str)
{
	int	i;
	int	counter;

	counter = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',' && str[i + 1] != '\0' && ft_isdigit(str[i + 1]) == 1)
			counter ++;
		i ++;
	}
	if (counter != 3)
		return (1);
	return (0);
}

int	check_for_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',' || str[i] == '\n')
			i ++;
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i ++;
	}
	return (0);
}

int	compare_strings(char *first, char *second)
{
	int	i;
	int	j;

	i = 0;
	while(first[i] != '\0')
	{
		j = 0;
		while(second[j] != '\0')
		{
			if (first[i] == second[j])
				return (1);
			j ++;
		}
		i++;
	}
	return (0);
}

void	check_for_spaces(char *str, int flag)
{
	if(compare_strings(str, WHITESPACES) == 1)
	{
		if (flag == 1)
			print_error("There are whitespaces in the floor color");
		if (flag == 2)
			print_error("There are whitespaces in the ceiling color");
		// free
		exit (1);
	}
}
