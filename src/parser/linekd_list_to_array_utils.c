#include "cub3d.h"

int	check_if_allowed_character(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'D' || str[i] == 'E'
			|| str[i] == 'S' || str[i] == '1' || str[i] == '0' || str[i] == ' '
			|| str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}
