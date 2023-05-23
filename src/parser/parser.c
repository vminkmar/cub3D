#include "../../include/cub3d.h"

void	compare_textures(t_data *data)
{
	t_tex_list *tmp;

	tmp = data->t_list;
	while (tmp)
	{
		if (ft_strncmp("NO", tmp->content, 2) == 0)
		{
			data->map->path_north = get_string_path(tmp->content, data);
			data->map->path_north_counter++;
		}
		else if (ft_strncmp("SO",  tmp->content, 2) == 0)
		{
			data->map->path_south = get_string_path(tmp->content, data);
			data->map->path_south_counter++;
		}
		else if (ft_strncmp("EA",  tmp->content, 2) == 0)
		{
			data->map->path_east = get_string_path(tmp->content, data);
			data->map->path_east_counter++;

		}
		else if (ft_strncmp("WE",  tmp->content, 2) == 0)
		{
			data->map->path_west = get_string_path(tmp->content, data);
			data->map->path_west_counter++;
		}
		else if (ft_strncmp("F",  tmp->content, 1) == 0)
		{
			data->map->floor_color = get_string_path(tmp->content, data);
			data->map->floor_color_counter++;
		}
		else if (ft_strncmp("C",  tmp->content, 1) == 0)
		{
			data->map->ceiling_color = get_string_path(tmp->content, data);
			data->map->ceiling_color_counter++;
		}
		 tmp =  tmp->next;	
	}
}

void	check_for_empty_textures(t_data *data)
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
	if (error != ERROR_NO)
		print_wrong_textures(data, error);
}

void	check_for_mutiple_textures(t_data *data)
{
	t_error	error;

	error = ERROR_NO;
	if (data->map->path_east_counter > 1)
		error = ERROR_EAST_MULTIPLE;
	else if (data->map->path_north_counter > 1)
		error = ERROR_NORTH_MULTIPLE;
	else if (data->map->path_south_counter > 1)
		error = ERROR_SOUTH_MULTIPLE;
	else if (data->map->path_west_counter > 1)
		error = ERROR_WEST_MULTIPLE;
	else if (data->map->floor_color_counter > 1)
		error = ERROR_FLOOR_MULTIPLE;
	else if (data->map->ceiling_color_counter > 1)
		error = ERROR_CEILING_MULTIPLE;
	if (error != ERROR_NO)
		print_multiple_textures(data, error);
}

// int	upper_case_check(char *str)
// {
// 	int i;

// 	i = 0;
// 	if (str[i] < 'A' || str[i] > 'Z' )
// 		return (1);
// 	while(str[i] >= 'A' && str[i] <= 'Z')
// 		i++;
// 		if (ft_charcmp(str[i], WHITESPACES_LESS) == 1)
// 			return (2);
// 		if (str[i] != ' ')
// 			return (1);
// 	return (0);
// }

// void check_if_error(int error)
// {
// 	if (error == 1)
// 		print_error("Error\nCheck the syntax of the textures");
// 	if (error == 2)
// 		print_error("Error\nCheck for whitespaces in the textures");
// 	if (error != 0)
// 	{
// 		// free
// 		exit (1);
// 	}
// }

// void check_for_upper_case(t_data *data)
// {
// 	int error;
// 	t_tex_list *tmp;

// 	tmp = data->t_list;
// 	error = 0;
// 	while(tmp)
// 	{
// 		error = upper_case_check(tmp->content);
// 		check_if_error(error);
// 		tmp = tmp->next;
// 	}
// }

void	compare_and_check_textures(t_data *data)
{
	trim_before_and_after(data);
	// check_for_upper_case(data);
	trim_spaces_textures(data);
	syntax_textures(data);
	compare_textures(data);
	check_for_empty_textures(data);
	check_for_mutiple_textures(data);
	get_color_floor(data);
	get_color_ceiling(data);
}

void print_wrong_pngs(t_data *data, t_error error)
{
	if (error == ERROR_NORTH)
		print_error("Error\nFailed to load north texture");
	if (error == ERROR_SOUTH)
		print_error("Error\nFailed to load south texture");
	if (error == ERROR_WEST)
		print_error("Error\nFailed to load west texture");
	if (error == ERROR_EAST)
		print_error("Error\nFailed to load east texture");
	if (error == ERROR_DOOR)
		print_error("Error\nFailed to load door texture");
	if (error == ERROR_DOOR_ONE)
		print_error("Error\nFailed to load door texture");
	free_all(data);
	exit(1);
}

void load_pngs(t_data *data)
{
	t_error error;

	error = ERROR_NO;
	data->map->tex_north = mlx_load_png(data->map->path_north);
	if (data->map->tex_north == NULL)
		error = ERROR_NORTH;
	data->map->tex_south = mlx_load_png(data->map->path_south);
	if (data->map->tex_south == NULL)
		error = ERROR_SOUTH;
	data->map->tex_west = mlx_load_png(data->map->path_west);
	if (data->map->tex_west == NULL)
		error = ERROR_WEST;
	data->map->tex_east = mlx_load_png(data->map->path_east);
	if (data->map->tex_east == NULL)
		error = ERROR_EAST;
	data->map->tex_door[0] = mlx_load_png("./textures/door_green.png");
	if (data->map->tex_door == NULL)
		error = ERROR_DOOR;
	data->map->tex_door[1] = mlx_load_png("./textures/door_red.png");
	if (data->map->tex_door == NULL)
		error = ERROR_DOOR_ONE;
	if (error != ERROR_NO)
		print_wrong_pngs(data, error);
}

void check_number_of_textures(t_data *data)
{
	if (data->t_list->counter > 6)
	{
		print_error("Error\nThere are too many textures");
		free_all(data);
		exit (1);
	}
}

void	parser(char **argv, t_data *data)
{
	create_linked_list_for_textures(&data);
	create_linked_list_for_map(&data);
	init_variables(data);
	get_textures_and_map(argv, data);
	check_number_of_textures(data);
	compare_and_check_textures(data);
	data->map->map = transfer_map_to_array(data);
	check_map(data->map->map, data);
	load_pngs(data);
	free_list_textures(&data->t_list);
	free_list_map(&data->m_list);
}
