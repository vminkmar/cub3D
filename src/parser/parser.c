#include "cub3d.h"

void	compare_textures(t_tex_list *tex, t_var *var)
{
	while (tex)
	{
		if (ft_strncmp("NO ", tex->content, 3) == 0)
			var->path_north = get_string_path(tex->content);
		else if (ft_strncmp("SO ", tex->content, 3) == 0)
			var->path_south = get_string_path(tex->content);
		else if (ft_strncmp("EA ", tex->content, 3) == 0)
			var->path_east = get_string_path(tex->content);
		else if (ft_strncmp("WE ", tex->content, 3) == 0)
			var->path_west = get_string_path(tex->content);
		else if (ft_strncmp("F ", tex->content, 2) == 0)
			var->floor_color = get_string_path(tex->content);
		else if (ft_strncmp("C ", tex->content, 2) == 0)
			var->ceiling_color = get_string_path(tex->content);
		tex = tex->next;
	}
}

void	check_textures(t_tex_list *tex, t_var *var)
{
	int		flag;
	t_error	error;

	error = ERROR_NO;
	flag = 0;
	if (var->path_east == NULL)
		error = ERROR_EAST;
	else if (var->path_north == NULL)
		error = ERROR_NORTH;
	else if (var->path_south == NULL)
		error = ERROR_SOUTH;
	else if (var->path_west == NULL)
		error = ERROR_WEST;
	else if (var->floor_color == NULL)
		error = ERROR_FLOOR;
	else if (var->ceiling_color == NULL)
		error = ERROR_CEILING;
	else if (error != ERROR_NO)
		print_wrong_textures(tex, var, error);
}

void	compare_and_check_textures(t_tex_list *tex, t_var *var)
{
	trim_spaces_textures(tex);
	compare_textures(tex, var);
	check_textures(tex, var);
	check_colors(var);
	get_color_floor(var);
	get_color_ceiling(var);
}

void	parser(char **argv, t_var *var, t_map_list *map, t_tex_list *tex)
{
	create_linked_list_for_textures(&tex);
	create_linked_list_for_map(&map);
	init_variables(var, map, tex);
	get_textures_and_map(argv, map, tex, var);
	compare_and_check_textures(tex, var);
	var->map.map = transfer_map_to_array(map, var);
	check_map(var->map.map, var);
	free_list_textures(&tex);
	free_list_map(&map);
}
