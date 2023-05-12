#include "../../include/cub3d.h"

char	*trim_spaces_utils(char *str, char *content, int new, int flag)
{
	int		old;

	old = 0;
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
			continue ;
		}
		else
			content[new] = str[old];
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

void	trim_spaces_textures(t_tex_list *tex)
{
	char	*new;

	new = NULL;
	while (tex != NULL)
	{
		new = tex->content;
		tex->content = trim_spaces_string(tex->content);
		free(new);
		tex = tex->next;
	}
}

char	*get_string_path(char *str)
{
	char	*new_str;
	int		i;
	int		flag;
	int		j;

	i = 0;
	j = 0;
	flag = 0;
	new_str = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i] != ' ' && flag == 0 && str[i] != '\0')
		i++;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
