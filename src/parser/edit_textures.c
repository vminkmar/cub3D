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

char	*trim_spaces_utils(char *str, char *content, int new, int flag)
{
	int		old;
	int		flag_for_begin;

	old = 0;
	flag_for_begin = 0;
	while (str[old] >= 'A' && str[old] <= 'Z')
	{
		content[new] = str[old];
		old++;
		new++;
	}
	while (str[old] != '\0')
	{
		if (str[old] == ' ' && flag == 0)
		{
			flag = 1;
			content[new] = str[old];
		}
		else if (str[old] == ' ' && flag == 1 && flag_for_begin != 1)
		{
			old++;
			continue ;
		}
		else
		{
			content[new] = str[old];
			flag_for_begin = 1;
		}
		old++;
		new++;
	}
	content[new] = '\0';
	return (content);
}

char	*trim_spaces_string(char *str)
{
	int		new;
	int		flag;
	char	*content;

	new = 0;
	flag = 0;
	content = malloc(strlen(str) + 1);
	content = trim_spaces_utils(str, content, new, flag);
	return (content);
}

void	trim_spaces_textures(t_data *data)
{
	char		*new;
	t_tex_list	*tmp;

	tmp = data->t_list;
	new = NULL;
	while (tmp != NULL)
	{
		new = tmp->content;
		tmp->content = trim_spaces_string(tmp->content);
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
