#include "cub3d.h"

int	count_lines(t_map_list *map)
{	
	t_map_list	*tmp;
	int			counter;

	counter = 0;
	tmp = map;
	while (tmp != NULL)
	{
		counter ++;
		tmp = tmp->next;
	}
	return (counter);
}

char	**transfer_map_to_array(t_map_list *map)
{
	int		line_counter;
	char	**map_data;
	int		i;

	i = 0;
	line_counter = count_lines(map);
	map_data = malloc(sizeof(char *) *(line_counter + 1));
	while (map)
	{
		map_data[i] = ft_strdup(map->content);
		i ++;
		map = map->next;
	}
	map_data[i] = NULL;
	return (map_data);
}
