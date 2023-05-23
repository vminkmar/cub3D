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
	*tex = NULL;
}

void free_data(t_data *data)
{
	free(data->map->tex_door);
	free(data->map->path_north);
	free(data->map->path_south);
	free(data->map->path_west);
	free(data->map->path_east);
	free(data->map->floor_color);
	free(data->map->ceiling_color);
}


void free_textures(t_data *data)
{
	if (data->map->tex_north == NULL || data->map->tex_east == NULL
		|| data->map->tex_west == NULL || data->map->tex_south == NULL
		|| data->map->tex_door[0] == NULL || data->map->tex_door[1] == NULL)
	{
		if (data->map->tex_north != NULL)
			mlx_delete_texture(data->map->tex_north);
		if (data->map->tex_south != NULL)
			mlx_delete_texture(data->map->tex_south);
		if (data->map->tex_west != NULL)
			mlx_delete_texture(data->map->tex_west);
		if (data->map->tex_east != NULL)
			mlx_delete_texture(data->map->tex_east);
		if (data->map->tex_door[0] != NULL)
			mlx_delete_texture(data->map->tex_door[0]);
		if (data->map->tex_door[1] != NULL)
			mlx_delete_texture(data->map->tex_door[1]);
	}
}

void free_all(t_data *data)
{
	free_list_map(&data->m_list);
	free_list_textures(&data->t_list);
	free_textures(data);
	free_data(data);
	ft_free2d(data->map->map);
	free(data->player);
	free(data->map);
	free(data);
}

void	free_list_map(t_map_list **map)
{
	t_map_list	*head = *map;
	t_map_list	*tmp;

	while (head)
	{
		free(head->content);
		tmp = head->next;
		free(head);
		head = tmp;
	}
	*map = NULL;
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
	numbers = NULL;
}
