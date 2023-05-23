#include "../../include/cub3d.h"

void	get_textures(char *line, t_data *data)
{
	char	*trimmed;

	if (!line)
		return ;
	if (line[0] == '\n')
	{
		free (line);
		return ;
	}
	trimmed = ft_strtrim(line, WHITESPACES);
	free(line);
	if (!trimmed)
		return ;
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		return ;
	}
	add_node_to_tex(trimmed, &data);
	data->t_list->counter ++;
}

void	get_map(char *line, t_data *data)
{
	check_for_empty_line(line, data);
	if (data->m_list->empty_line == 1 && is_begin_of_map(line) == 0)
	{
		print_error("Error\nThere is an empty line in the Map");
		exit(1);
	}
	add_node_to_map(line, &data);
	data->map->max_height++;
}

void	get_textures_and_map(char **argv, t_data *data)
{
	int		fd;
	char	*line;
	int		begin_of_map;

	begin_of_map = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_error("Error\nThere is no map with that name or the map is empty");
		free_all(data);
		exit (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
		{
			free(line);
			break ;
		}
		if (is_begin_of_map(line) == 1 && begin_of_map == 0)
			get_textures(line, data);
		else
		{
			begin_of_map = 1;
			get_map(line, data);
		}
	}
	if (begin_of_map == 0)
	{
		print_error("Error\nThere is no Map in that file");
		free_all(data);
		exit (1);
	}
	close (fd);
}
