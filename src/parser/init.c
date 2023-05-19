#include "cub3d.h"

void	init_variables(t_data *data, t_map_list *maps, t_tex_list *tex)
{
	data->map->path_east = NULL;
	data->map->path_south = NULL;
	data->map->path_west = NULL;
	data->map->path_north = NULL;
	data->map->floor_color = NULL;
	data->map->ceiling_color = NULL;
	data->map->color_ceiling = 0;
	data->map->color_ceiling = 0;
	data->map->color_ceiling = 0;
	data->map->color_ceiling = 0;
	data->map->path_east_counter = 0;
	data->map->path_south_counter =0;
	data->map->path_west_counter = 0;
	data->map->path_north_counter = 0;
	data->map->floor_color_counter = 0;
	data->map->ceiling_color_counter = 0;
	data->map->max_height = 0;
	data->map->max_width = 0;
	data->map->color_floor = 0;
	data->player->counter_p_start = 0;
	data->player->p_start.x = 0;
	data->player->p_start.y = 0;
	maps->empty_line = 0;
	tex->counter = 0;
}
