#include "cub3d.h"

void	init_variables(t_var *var, t_map_list *map, t_tex_list *tex)
{
	var->path_east = NULL;
	var->path_south = NULL;
	var->path_west = NULL;
	var->path_north = NULL;
	var->floor_color = NULL;
	var->ceiling_color = NULL;
	var->color_ceiling = 0;
	var->map.height = 0;
	var->color_floor = 0;
	map->empty_line = 0;
	tex->counter = 0;
}
