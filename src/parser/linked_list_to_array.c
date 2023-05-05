#include "cub3d.h"

void get_start_point(t_var *var, char c, int line, int character)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		var->map.player.start.y = line;
		var->map.player.start.x = character;
		var->map.player.start_points ++;
	}	
}

void check_for_startpoint(t_var *var)
{
	if(var->map.player.start_points < 1)
		print_error("There is no start point on the map");
	if(var->map.player.start_points > 1)
		print_error("There are too many startpoints on the map");
	// free
	exit (1);
}

char	*get_map_types(const char *s1, int line, t_var *var)
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
		get_start_point(var, s1[character], line, character);
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

char	**transfer_map_to_array(t_map_list *map, t_var *var)
{
	char	**map_data;
	int		line;

	line = 0;
	map_data = malloc(sizeof(t_type *) *(var->map.height + 1));
	while (map)
	{
		map_data[line] = get_map_types(map->content, line, var);
		line ++;
		map = map->next;
	}
	map_data[line] = NULL;
	check_for_startpoint(var);
	return (map_data);
}
