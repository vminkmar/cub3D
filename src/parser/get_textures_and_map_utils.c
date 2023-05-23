#include "../../include/cub3d.h"

int	is_wall_or_field(char type)
{
	if (type == '1' || type == '0' || type == ' ' || type == '\n')
		return (0);
	return (1);
}

void	check_for_empty_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		data->m_list->empty_line = 1;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (ft_strcmp(&line[i], WHITESPACES) == 1)
			return ;
		if (ft_strcmp(&line[i], WHITESPACES) == 0)
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			data->m_list->empty_line = 1;
	}
}


int is_start_point(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

int	is_begin_of_map(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (1);
	while (line[i] != '\n' && line[i] != '\0')
	{
		while (ft_charcmp(line[i], WHITESPACES) == 1)
			i++;
		if (is_start_point(line[i]) == 0)
			i++;
		if (is_wall_or_field(line[i]) == 1)
			return (1);
		while (is_wall_or_field(line[i]) == 0)
			i++;
	}
	return (0);
}
