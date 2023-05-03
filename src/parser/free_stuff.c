#include "cub3d.h"

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

void	free_var(t_var *var)
{
	if (var != NULL)
	{
		if (var->ceiling_color != NULL)
			free(var->ceiling_color);
		if (var->floor_color != NULL)
			free(var->floor_color);
		if (var->path_east != NULL)
			free(var->path_east);
		if (var->path_north != NULL)
			free(var->path_north);
		if (var->path_west != NULL)
			free(var->path_west);
		if (var->path_south != NULL)
			free(var->path_south);
		if (var->ceiling_color != NULL)
			free(var->ceiling_color);
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
