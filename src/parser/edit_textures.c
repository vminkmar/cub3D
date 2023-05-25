/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:28:17 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/25 12:28:18 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	trim_before_and_after(t_data *data)
{
	char		*new;
	t_tex_list	*tmp;

	tmp = data->t_list;
	new = NULL;
	while (tmp != NULL)
	{
		new = tmp->content;
		tmp->content = ft_strtrim(tmp->content, WHITESPACES);
		free(new);
		tmp = tmp->next;
	}
}

void	get_string_path_utils(char *str, t_data *data, int *old)
{
	while (str[*old] >= 'A' && str[*old] <= 'Z')
		(*old)++;
	if (str[*old] != ' ')
	{
		print_error("Error\nCheck the texture names");
		free_all(data);
		exit (1);
	}
}

char	*get_string_path(char *str, t_data *data)
{
	char	*new_str;
	int		old;
	int		flag;
	int		new;

	old = 0;
	new = 0;
	flag = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	get_string_path_utils(str, data, &old);
	while (str[old] == ' ')
		old++;
	while (str[old] != '\0')
	{
		if (str[old] == '\n')
			old ++;
		new_str[new] = str[old];
		new++;
		old++;
	}
	new_str[new] = '\0';
	return (new_str);
}
