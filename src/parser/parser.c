#include "../../include/cub3d.h"

void	check_number_of_textures(t_data *data)
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
	transfer_map_to_array(data);
	check_map(data->map->map, data);
	load_pngs(data);
	free_list_textures(&data->t_list);
	free_list_map(&data->m_list);
}
