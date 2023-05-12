#include "../../include/cub3d.h"

void	create_linked_list_for_textures(t_tex_list **tex)
{
	*tex = malloc(sizeof(t_tex_list));
	if (*tex == NULL)
	{
		print_error("Allocating Memory failed");
		exit(1);
	}
	(*tex)->next = NULL;
	(*tex)->content = NULL;
}

void	create_linked_list_for_map(t_map_list **map)
{
	*map = malloc(sizeof(t_map_list));
	if (*map == NULL)
	{
		print_error("Allocating Memory failed");
		exit(1);
	}
	(*map)->next = NULL;
	(*map)->content = NULL;
}

void	add_node_to_map(char *line, t_map_list **map)
{
	t_map_list	*new_map;

	if ((*map)->content == NULL)
		(*map)->content = ft_strdup(line);
	else
	{
		new_map = malloc(sizeof(t_map_list));
		if (new_map == NULL)
		{
			print_error("Allocation of Memory failed");
			// free
			exit (1);
		}
		new_map->next = NULL;
		new_map->content = ft_strdup(line);
		ft_lstadd_back_map(map, new_map);
		free(line);
	}
}

void	add_node_to_tex(char *line, t_tex_list **tex)
{
	t_tex_list	*new_tex;

	if ((*tex)->content == NULL)
		(*tex)->content = ft_strdup(line);
	else
	{
		new_tex = malloc(sizeof(t_tex_list));
		if (new_tex == NULL)
		{
			print_error("Allocation of Memory failed");
			// free
			exit (1);
		}
		new_tex->next = NULL;
		new_tex->content = ft_strdup(line);
		ft_lstadd_back_tex(tex, new_tex);
	}
}
