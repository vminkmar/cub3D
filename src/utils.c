#include "cub3d.h"

char	*stupid_shit( char *s1, char *s2)
{
	size_t	c;
	size_t	d;
	char	*a;

	c = ft_strlen(s1);
	d = ft_strlen(s2);
	a = malloc((c + d) * sizeof(char) + 1);
	if (a == NULL)
		return (NULL);
	return (a);
}

char	*sl_strjoin(char *s1, char *s2)
{
	char	*a;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (0);
	a = stupid_shit(s1, s2);
	while (s1[i] != '\0')
	{
		a[i] = s1[i];
		i ++;
	}
	while (s2[j] != '\0')
	{
		a[i] = s2[j];
		i++;
		j++;
	}
	a[i] = '\0';
	free(s1);
	return (a);
}

int	ft_strcmp(char *first, char *second)
{
	int	counter_first;
	int	counter_second;

	counter_first = 0;
	while (first[counter_first] != '\0')
	{
		counter_second = 0;
		while (second[counter_second] != '\0')
		{	
			if (first[counter_first] != second[counter_second])
				return (1);
			counter_second++;
		}
		counter_first ++;
	}
	return (0);
}

void	ft_free2d(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	if (s)
		free(s);
}

void	free_exit(t_data *data)
{
	free(data->player);
	mlx_delete_texture(data->map->tex_north);
	mlx_delete_texture(data->map->tex_south);
	mlx_delete_texture(data->map->tex_west);
	mlx_delete_texture(data->map->tex_east);
	mlx_delete_texture(data->map->tex_door[0]);
	mlx_delete_texture(data->map->tex_door[1]);
	free(data->map->tex_door);
	free(data->map->path_north);
	free(data->map->path_south);
	free(data->map->path_west);
	free(data->map->path_east);
	free(data->map->floor_color);
	free(data->map->ceiling_color);
	ft_free2d(data->map->map);
	free(data->map);
	mlx_terminate(data->mlx);
	free(data);
}
