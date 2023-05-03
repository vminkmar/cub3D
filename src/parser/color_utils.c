#include "cub3d.h"

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
		if (str[i] == ',')
			i ++;
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i ++;
	}
	return (0);
}
