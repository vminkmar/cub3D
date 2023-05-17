#include "../../include/cub3d.h"

void get_start_point(t_data *data, char c, int line, int character)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->player->p_start.y = line + 0.5;
		data->player->p_start.x = character + 0.5;
		if(c == 'N')
            data->player->angle = 270;
		if(c == 'S')
            data->player->angle = 90;
        if(c == 'E')
            data->player->angle = 0;
        if(c == 'W')
            data->player->angle = 180;
		data->player->counter_p_start ++;
	}	
}

void check_for_startpoint(t_data *data)
{
	if(data->player->counter_p_start < 1)
		print_error("There is no start point on the map");
	if(data->player->counter_p_start > 1)
		print_error("There are too many startpoints on the map"); // edit
}

char	*get_map_types(const char *s1, int line, t_data *data)
{
	char	*new;
	size_t	character;

	if (s1 == NULL)
		return (NULL);
	new = malloc(sizeof(t_type *) * (ft_strlen(s1) + 1));
	if (new == NULL)
		return (NULL);
	character = 0;
	while (character < ft_strlen(s1) + 1)
	{	
		get_start_point(data, s1[character], line, character);
		if(s1[character] == '1')
			new[character] = WALL;
		else if(s1[character] == '0')
			new[character] = WALKABLE;
		else
			new[character] = s1[character];
		character++;
	}
	return (new);
}

void get_max_width(char *str, t_data *data)
{
	int length;

	length = ft_strlen(str);
	if(length > data->map->max_width)
		data->map->max_width = length;
}

char	**transfer_map_to_array(t_map_list *map, t_data *data)
{
	char	**map_data;
	int		line;

	line = 0;
	map_data = malloc(sizeof(t_type *) *(data->map->max_height + 1));
	while (map)
	{
		map_data[line] = get_map_types(map->content, line, data);
		get_max_width(map_data[line], data);
		line ++;
		map = map->next;
	}
	map_data[line] = NULL;
	check_for_startpoint(data);
	return (map_data);
}
