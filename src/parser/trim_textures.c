#include "cub3d.h"

char	*trim_spaces_utils_utils(char *str, char *content, t_utils util)
{
	while (str[util.old] != '\0')
	{
		if (str[util.old] == ' ' && util.flag == 0)
		{
			util.flag = 1;
			content[util.new] = str[util.old];
		}
		else if (str[util.old] == ' ' && util.flag == 1
			&& util.flag_for_begin != 1)
		{
			util.old++;
			continue ;
		}
		else
		{
			content[util.new] = str[util.old];
			util.flag_for_begin = 1;
		}
		util.old++;
		util.new++;
	}
	return (content[util.new] = '\0', content);
}

char	*trim_spaces_utils(char *str, char *content, t_utils util)
{
	while (str[util.old] >= 'A' && str[util.old] <= 'Z')
	{
		content[util.new] = str[util.old];
		util.old++;
		util.new++;
	}
	content = trim_spaces_utils_utils(str, content, util);
	return (content);
}

char	*trim_spaces_string(char *str)
{
	t_utils	util;
	char	*content;

	util.new = 0;
	util.flag = 0;
	util.flag_for_begin = 0;
	util.old = 0;
	content = malloc(strlen(str) + 1);
	content = trim_spaces_utils(str, content, util);
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
