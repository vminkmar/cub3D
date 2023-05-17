#include "../../include/cub3d.h"

int	is_wall_or_field(char type)
{
	if (type == '1' || type == '0')
		return (0);
	return (1);
}

void	check_for_empty_line(char *line, t_map_list *map)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		map->empty_line = 1;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (ft_strcmp(&line[i], WHITESPACES) == 1)
			return ;
		if (ft_strcmp(&line[i], WHITESPACES) == 0)
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			map->empty_line = 1;
	}
}

int	is_begin_of_map(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (1);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (is_wall_or_field(line[i]) == 1)
			return (1);
		while (ft_strcmp(&line[i], WHITESPACES) == 0)
			i++;
		while (is_wall_or_field(line[i]) == 0)
			i++;
	}
	return (0);
}
