#include "../../include/cub3d.h"

mlx_texture_t	*get_tex(t_data *data, t_ray *ray)
{
	if (data->map->map[(int)ray->interception.y][(int)ray->map_check.x]
		== CLOSED_DOOR)
	{
		if ((data->framecount / 30 )% 2)
			return (data->map->tex_door[0]);
		else
			return (data->map->tex_door[1]);	
	}
	if (ray->wall_side == 0)
	{
		if (ray->step.x >= 0)
			return (data->map->tex_west);
		else
			return (data->map->tex_east);
	}
	else
	{
		if (ray->step.y >= 0)
			return (data->map->tex_north);
		else
			return (data->map->tex_south);
	}
}

int	get_x_pos(t_player *player, t_ray *ray, mlx_texture_t *tex)
{
	double	wall_hit;
	int		x_pos;

	if (ray->wall_side == 0)
		wall_hit = player->p_start.y + ray->distance * ray->dir.y;
	else
		wall_hit = player->p_start.x + ray->distance * ray->dir.x;
	x_pos = (int)((wall_hit - floor(wall_hit)) * tex->width);
	if ((ray->wall_side == 0 && ray->dir.x > 0)
		|| (ray->wall_side == 1 && ray->dir.y < 0))
		x_pos = tex->width - x_pos;
	return (x_pos);
}

void	paint_texture(t_data *data, t_ray *ray, int x)
{
	t_ivector		vtex;
	double			tex_pos;
	double			tex_step;
	mlx_texture_t	*tex;
	int				i;

	tex = get_tex(data, ray);
	vtex.x = get_x_pos(data->player, ray, tex);
	tex_step = tex->height / ray->proj_wall_height;
	tex_pos = (ray->wall_start - HEIGHT / 2
			+ ray->proj_wall_height / 2) * tex_step;
	vtex.x = tex->width - vtex.x;
	i = ray->wall_start;
	while (i < ray->wall_end)
	{
		vtex.y = (int)tex_pos % tex->height;
		ft_memcpy(&data->img->pixels[(WIDTH * i + x) * 4],
			&tex->pixels[(tex->width * vtex.y + vtex.x) * 4], 4);
		tex_pos += tex_step;
		i++;
	}
}

void	paint_background(t_data *data, t_ray *ray, int x)
{
	int	i;

	i = 0;
	while (i <= HEIGHT)
	{
		if (i <= ray->wall_start)
			draw_pixel(data->img, x, i, data->map->color_ceiling);
		else if (i >= ray->wall_end)
			draw_pixel(data->img, x, i, data->map->color_floor);
		i++;
	}
}
