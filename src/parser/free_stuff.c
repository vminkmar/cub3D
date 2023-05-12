#include "../../include/cub3d.h"

void	free_list_textures(t_tex_list **tex)
{
	t_tex_list	*tmp;

	if (tex != NULL)
	{
		tmp = (*tex);
		while ((*tex) != NULL)
		{
			tmp = (*tex);
			(*tex) = (*tex)->next;
			free(tmp->content);
			free(tmp);
		}
	}
}

void	free_list_map(t_map_list **map)
{
	t_map_list	*tmp;

	if (map != NULL)
	{
		tmp = (*map);
		while ((*map) != NULL)
		{
			tmp = (*map);
			(*map) = (*map)->next;
			free(tmp->content);
			free(tmp);
		}
	}
}

void	free_data(t_data *data)
{
	if (data != NULL)
	{
		if (data->map->ceiling_color != NULL)
			free(data->map->ceiling_color);
		if (data->map->floor_color != NULL)
			free(data->map->floor_color);
		if (data->map->path_east != NULL)
			free(data->map->path_east);
		if (data->map->path_north != NULL)
			free(data->map->path_north);
		if (data->map->path_west != NULL)
			free(data->map->path_west);
		if (data->map->path_south != NULL)
			free(data->map->path_south);
		if (data->map->ceiling_color != NULL)
			free(data->map->ceiling_color);
	}
}

void	free_numbers(char **numbers)
{
	int	i;

	i = 0;
	while (numbers[i] != NULL)
	{
		free(numbers[i]);
		i ++;
	}
	free(numbers);
}
