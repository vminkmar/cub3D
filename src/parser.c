/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:31:12 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/03 17:59:49 by vminkmar         ###   ########.fr       */
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
	var->color_ceiling = 0;
	var->color_floor = 0;
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

void	get_textures(char *line, t_tex_list *tex)
{
	char	*new;
	
	if (line[0] == '\n')
		return ;
	new = line;
	line = ft_strtrim(line, WHITESPACES);
	free (new);
	if (line[0] == '\0')
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
	while (line[i] != '\n' && line[i] != '\0')
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
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (ft_strcmp(&line[i], WHITESPACES) == 1)
			return ;
		if (ft_strcmp(&line[i], WHITESPACES) == 0)
			i++;
		if (line[i] == '\n' || line[i] == '\0')
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
	while (1)
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

char *trim_string(char *str)
{
	int		old;
	int		new;
	int		flag;
	char	*content;

	old = 0;
	new = 0;
	flag = 0;
	content = malloc(strlen(str) + 1);
	while (str[old] != '\0')
	{
		if (str[old] == ' ' && flag == 0)
		{
			flag = 1;
			content[new] = str[old];
		}
		else if (str[old] == ' ' && flag == 1)
		{
			old++;
			continue;
		}
		else
			content[new] = str[old];
		old++;		
		new++;
	}
	content[new] = '\0';
	return (content);
}

void trim_textures(t_tex_list *tex)
{
	char *new;
	while (tex != NULL)
	{
		new = tex->content;
		tex->content = trim_string(tex->content);
		free(new);
		tex = tex->next;
	}
}

char *get_string_path(char *str)
{
	char	*new_str;
	int		i;
	int		flag;
	int		j;

	i = 0;
	j = 0;
	flag = 0;
	new_str = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while(str[i] != ' ' && flag == 0 && str[i] != '\0')
		i++;
	while(str[i] == ' ' && str[i] != '\0')
		i++;
	while(str[i] != '\0')
	{
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[i] = '\0';
	return(new_str);
}

void compare_textures(t_tex_list *tex, t_var *var)
{
	while (tex)
	{
		if(ft_strncmp("NO ", tex->content, 3) == 0)
			var->path_north = get_string_path(tex->content);
		if(ft_strncmp("SO ", tex->content, 3) == 0)
			var->path_south = get_string_path(tex->content);
		if(ft_strncmp("EA ", tex->content, 3) == 0)
			var->path_east = get_string_path(tex->content);
		if(ft_strncmp("WE ", tex->content, 3) == 0)
			var->path_west = get_string_path(tex->content);
		if(ft_strncmp("F ", tex->content, 2) == 0)
			var->floor_color = get_string_path(tex->content);
		if(ft_strncmp("C ", tex->content, 2) == 0)
			var->ceiling_color = get_string_path(tex->content);
		tex = tex->next;
	}
}

void	print_wrong_textures(t_tex_list *tex, t_var *var, t_error error)
{
	if (error == ERROR_EAST)
		print_error("There is no east texture or you choose the wrong one");
	if (error == ERROR_NORTH)
		print_error("There is no north texture or you choose the wrong one");
	if (error == ERROR_SOUTH)
		print_error("There is no south texture or you choose the wrong one");
	if (error == ERROR_WEST)
		print_error("There is no west texture or you choose the wrong one");
	if (error == ERROR_FLOOR)
		print_error("There is no floor color or you choose the wrong one");
	if (error == ERROR_CEILING)
		print_error("There is no ceiling color or you choose the wrong one");
	var = NULL;
	free_list_textures(&tex);
	free_var(var);
	tex = NULL;
	exit (1);
}

void	check_textures(t_tex_list *tex, t_var *var)
{
	int	flag;
	t_error error;

	error = ERROR_NO;
	flag = 0;
	if (var->path_east == NULL)
		error = ERROR_EAST;
	if (var->path_north == NULL)
		error = ERROR_NORTH;
	if (var->path_south == NULL)
		error = ERROR_SOUTH;
	if (var->path_west == NULL)
		error = ERROR_WEST;
	if (var->floor_color == NULL)
		error = ERROR_FLOOR;
	if (var->ceiling_color == NULL)
		error = ERROR_CEILING;
	if (error != ERROR_NO)
		print_wrong_textures(tex, var, error);
}

uint32_t rgb_to_uint(int red, int green, int blue)
{
	uint32_t result;

	result = 0;
	result |= (uint32_t)red << 16;
	result |= (uint32_t)green << 8;
	result |= (uint32_t)blue;

	return (result);
}

void check_numbers(int red, int green, int blue)
{
	if(red > 256 || red < 0 || blue > 256 || blue < 0 || green > 256
		|| green < 0)
	{
		print_error("Wrong RGB color");
		// free
		exit (1);
	}
}

void get_color_floor(t_var *var)
{
	char	**numbers_floor;
	int		i;
	int		red;
	int		green;
	int		blue;

	i = 0;
	numbers_floor = ft_split((const char *)var->floor_color, ',');
	while(numbers_floor[i] != NULL)
	{
		if (i == 0)
			red = ft_atoi(numbers_floor[i]);
		if (i == 1)
			green = ft_atoi(numbers_floor[i]);
		if (i == 2)
			blue = ft_atoi(numbers_floor[i]);
		i ++;
	}
	check_numbers(red, green, blue);
	free_numbers(numbers_floor);
	var->color_floor = rgb_to_uint(red, green, blue);
}


void get_color_ceiling(t_var *var)
{
	char	**numbers_ceiling;
	int		i;
	int		red;
	int		green;
	int		blue;

	i = 0;
	numbers_ceiling = ft_split((const char *)var->ceiling_color, ',');
	while(numbers_ceiling[i] != NULL)
	{
		if (i == 0)
			red = ft_atoi(numbers_ceiling[i]);
		if (i == 1)
			green = ft_atoi(numbers_ceiling[i]);
		if (i == 2)
			blue = ft_atoi(numbers_ceiling[i]);
		i ++;
	}
	check_numbers(red, green, blue);
	free_numbers(numbers_ceiling);
	var->color_ceiling = rgb_to_uint(red, green, blue);
}

void compare_and_check_textures(t_tex_list *tex, t_var *var)
{
	trim_textures(tex);
	compare_textures(tex, var);
	check_textures(tex, var);
	get_color_floor(var);
	get_color_ceiling(var);

}

int count_lines(t_map_list *map)
{	
	t_map_list *tmp;
	int counter;

	counter = 0;
	tmp = map;
	while(tmp != NULL)
	{
		counter ++;
		tmp = tmp->next;
	}
	return (counter);
}

char **transfer_map_to_array(t_map_list *map)
{
	int		line_counter;
	char	**map_data;
	int		i;
	
	i = 0;
	line_counter = count_lines(map);
	map_data = malloc(sizeof(char *) *(line_counter + 1));
	while(map)
	{
		map_data[i] = ft_strdup(map->content);
		i ++;
		map = map->next;
	}
	map_data[i] = NULL;
	return (map_data);
}


void	parser(char **argv, t_var *var, t_map_list *map, t_tex_list *tex)
{
	create_linked_list_for_textures(&tex);
	create_linked_list_for_map(&map);
	init_variables(var, map, tex);
	get_textures_and_map(argv, map, tex);
	compare_and_check_textures(tex, var);
	var->map.map = transfer_map_to_array(map);
	free_list_textures(&tex);
	free_list_map(&map);
}