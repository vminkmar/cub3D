#include "../../include/cub3d.h"

void	compare_textures(t_tex_list *tex, t_data *data)
{
	while (tex)
	{
		if (ft_strncmp("NO ", tex->content, 3) == 0)
			data->map->path_north = get_string_path(tex->content);
		else if (ft_strncmp("SO ", tex->content, 3) == 0)
			data->map->path_south = get_string_path(tex->content);
		else if (ft_strncmp("EA ", tex->content, 3) == 0)
			data->map->path_east = get_string_path(tex->content);
		else if (ft_strncmp("WE ", tex->content, 3) == 0)
			data->map->path_west = get_string_path(tex->content);
		else if (ft_strncmp("F ", tex->content, 2) == 0)
			data->map->floor_color = get_string_path(tex->content);
		else if (ft_strncmp("C ", tex->content, 2) == 0)
			data->map->ceiling_color = get_string_path(tex->content);
		tex = tex->next;
	}
}

void	check_textures(t_tex_list *tex, t_data *data)
{
	t_error	error;

	error = ERROR_NO;
	if (data->map->path_east == NULL)
		error = ERROR_EAST;
	else if (data->map->path_north == NULL)
		error = ERROR_NORTH;
	else if (data->map->path_south == NULL)
		error = ERROR_SOUTH;
	else if (data->map->path_west == NULL)
		error = ERROR_WEST;
	else if (data->map->floor_color == NULL)
		error = ERROR_FLOOR;
	else if (data->map->ceiling_color == NULL)
		error = ERROR_CEILING;
	else if (error != ERROR_NO)
		print_wrong_textures(tex, data, error);
}

void	compare_and_check_textures(t_tex_list *tex, t_data *data)
{
	trim_spaces_textures(tex);
	compare_textures(tex, data);
	check_textures(tex, data);
	check_colors(data);
	get_color_floor(data);
	get_color_ceiling(data);
}

void load_pngs(t_data *data)
{
	data->map->tex_north = mlx_load_png(data->map->path_north);
	if (data->map->tex_north == NULL)
		print_error("north");
	data->map->tex_south = mlx_load_png(data->map->path_south);
	if (data->map->tex_south == NULL)
		print_error("south");
	data->map->tex_west = mlx_load_png(data->map->path_west);
	if (data->map->tex_west == NULL)
		print_error("west");
	data->map->tex_east = mlx_load_png(data->map->path_east);
	if (data->map->tex_east == NULL)
		print_error("east");
	data->map->tex_door[0] = mlx_load_png("./textures/door_green.png");
	if (data->map->tex_door == NULL)
		print_error("door0");
	data->map->tex_door[1] = mlx_load_png("./textures/door_red.png");
	if (data->map->tex_door == NULL)
		print_error("door1");
}

void	parser(char **argv, t_data *data)
{
	t_tex_list	*tex;
	t_map_list	*map;

	map = NULL;
	tex = NULL;
	create_linked_list_for_textures(&tex);
	create_linked_list_for_map(&map);
	init_variables(data, map, tex);
	get_textures_and_map(argv, map, tex, data);
	compare_and_check_textures(tex, data);
	data->map->map = transfer_map_to_array(map, data);
	check_map(data->map->map, data);
	load_pngs(data);
	free_list_textures(&tex);
	free_list_map(&map);
}
