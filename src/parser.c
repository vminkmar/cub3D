/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:31:12 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/02 13:33:20 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_variables(t_var *var, t_map_list *map, t_tex_list *tex)
{
	var->path_east = NULL;
	var->path_south = NULL;
	var->path_west = NULL;
	var->path_north = NULL;
	var->floor_color = NULL;
	var->ceiling_color = NULL;
	map->empty_line = 0;
	tex->counter = 0;
}

void	ft_lstadd_back_tex(t_tex_list **lst, t_tex_list *new)
{	
	t_tex_list	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{	
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstadd_back_map(t_map_list **lst, t_map_list *new)
{	
	t_map_list	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{	
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
			//free
			exit (1);
		}
		new_map->next = NULL;
		new_map->content = ft_strdup(line);
		ft_lstadd_back_map(map, new_map);
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
			exit (1);
		}
		new_tex->next = NULL;
		new_tex->content = ft_strdup(line);
		ft_lstadd_back_tex(tex, new_tex);
	}
}

void	get_textures(char *line, t_tex_list *tex)
{
	char	*new;
	
	if(line[0] == '\n')
		return ;
	new = line;
	line = ft_strtrim(line, WHITESPACES);
	free (new);
	if(line[0] == '\0')
		return ;
	add_node_to_tex(line, &tex);
	tex->counter ++;
}


int	is_wall_or_field(char type)
{
	if (type == '1' || type == '0')
		return (0);
	return(1);
}

int	is_begin_of_map(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (1);
	while(line[i] != '\n' && line[i] != '\0')
	{
		if (is_wall_or_field(line[i]) == 1)
			return (1);
		while (ft_strcmp(&line[i], WHITESPACES) == 0)
			i++;
		while (is_wall_or_field(line[i]) == 0)
			i++;
	}
	return (0);
}

void	check_for_empty_line(char *line, t_map_list *map)
{
	int i;
	
	i = 0;
	if (line[0] == '\n')
	{
		map->empty_line = 1;
	}
	while(line[i] != '\n' && line[i] != '\0')
	{
		if(ft_strcmp(&line[i], WHITESPACES) == 1)
			return ;
		if(ft_strcmp(&line[i], WHITESPACES) == 0)
			i++;
		if(line[i] == '\n' || line[i] == '\0')
			map->empty_line = 1;
	}
}

void	get_map(char *line, t_map_list *map)
{
	check_for_empty_line(line, map);
	if (map->empty_line == 1 && is_begin_of_map(line) == 0)
	{
		print_error("There is an empty line in the Map");
		exit(1);
	}
		add_node_to_map(line, &map);
}

void	get_textures_and_map(char **argv, t_map_list *map, t_tex_list *tex)
{
	int		fd;
	char	*line;
	int		begin_of_map = 0;
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_error("There is no map with that name");
		exit (1);
	}
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
			break ;
		if (is_begin_of_map(line) == 1 && begin_of_map == 0)
			get_textures(line, tex);
		else
		{
			begin_of_map = 1;
			get_map(line, map);
		}
	}
	close (fd);
}

// void trim_textures(t_tex_list *tex)
// {
	
// }

void compare_textures(t_tex_list *tex, t_var *var)
{
	while(tex)
	{
		if(ft_strncmp("NO ", tex->content, 3) == 0)
			var->path_north = ft_strdup(tex->content);
		if(ft_strncmp("SO ", tex->content, 3) == 0)
			var->path_south = ft_strdup(tex->content);
		if(ft_strncmp("EA ", tex->content, 3) == 0)
			var->path_east = ft_strdup(tex->content);
		if(ft_strncmp("WE ", tex->content, 3) == 0)
			var->path_west = ft_strdup(tex->content);
		if(ft_strncmp("F ", tex->content, 2) == 0)
			var->floor_color = ft_strdup(tex->content);
		if(ft_strncmp("C ", tex->content, 2) == 0)
			var->ceiling_color = ft_strdup(tex->content);
		tex = tex->next;
	}
}

void print_wrong_textures(t_tex_list *tex, t_var *var, int flag)
{
	if(flag == 1)
		print_error("There is no east texture");
	if(flag == 2)
		print_error("There is no north texture");
	if(flag == 3)
		print_error("There is no south texture");
	if(flag == 4)
		print_error("There is no west texture");
	if(flag == 5)
		print_error("There is no floor color");
	if(flag == 6)
		print_error("There is no ceiling color");
	free_textures(&tex);
	free_var(var);
	tex = NULL;
	exit (1);
}

void	check_textures(t_tex_list *tex, t_var *var)
{
	int	flag;

	flag = 0;
	if (var->path_east == NULL)
		flag = 1;
	if (var->path_north == NULL)
		flag = 2;
	if (var->path_south == NULL)
		flag = 3;
	if (var->path_west == NULL)
		flag = 4;
	if (var->floor_color == NULL)
		flag = 5;
	if (var->ceiling_color == NULL)
		flag = 6;
	if (flag != 0)
		print_wrong_textures(tex, var, flag);
}


void compare_and_check_textures(t_tex_list *tex, t_var *var)
{
	compare_textures(tex, var);
	check_textures(tex, var);
	// trim_textures(tex);

}


void	parser(char **argv, t_var *var, t_map_list *map, t_tex_list *tex)
{
	create_linked_list_for_textures(&tex);
	create_linked_list_for_map(&map);
	init_variables(var, map, tex);
	get_textures_and_map(argv, map, tex);
	compare_and_check_textures(tex, var);
}