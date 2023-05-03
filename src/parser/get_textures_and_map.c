#include "cub3d.h"

void	get_textures(char *line, t_tex_list *tex)
{
	char	*new;

	if (line[0] == '\n')
		return ;
	new = line;
	line = ft_strtrim(line, WHITESPACES);
	free (new);
	if (line[0] == '\0')
		return ;
	add_node_to_tex(line, &tex);
	tex->counter ++;
}

void	get_map(char *line, t_map_list *map, t_var *var)
{
	check_for_empty_line(line, map);
	if (map->empty_line == 1 && is_begin_of_map(line) == 0)
	{
		print_error("There is an empty line in the Map");
		exit(1);
	}
	add_node_to_map(line, &map);
	var->map.height++;
}

void	get_textures_and_map(char **argv, t_map_list *map, t_tex_list *tex,
			t_var *var)
{
	int		fd;
	char	*line;
	int		begin_of_map;

	begin_of_map = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_error("There is no map with that name");
		exit (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
			break ;
		if (is_begin_of_map(line) == 1 && begin_of_map == 0)
			get_textures(line, tex);
		else
		{
			begin_of_map = 1;
			get_map(line, map, var);
		}
	}
	close (fd);
}
