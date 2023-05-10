#include "../include/cub3d.h"

t_wall_orientation get_orientation(t_ray *ray, t_player *player)
{
	double	dx;
	double	dy;

	dx = player->p_start.x - ray->interception.x;
	dy = player->p_start.y - ray->interception.y;

	if(ray->wall_side == 0)
	{
		if (ray->step.x > 0)
			return (WEST);
		else if (ray->step.x < 0)
			return (EAST);
	}
	else if (ray->wall_side == 1)
	{
		if(ray->step.y >0)
			return (NORTH);
		else if (ray->step.x < 0)
			return (SOUTH);
	}
	return(4);
}

int get_x_pos(t_player *player, t_ray *ray, mlx_texture_t *tex)
{
	double	wall_hit;
	int		x_pos;

	if(ray->wall_side == 0)
		wall_hit = player->p_start.y + ray->distance * ray->dir.y;
	else
		wall_hit = player->p_start.x + ray->distance * ray->dir.x;
	x_pos = (int)((wall_hit - floor(wall_hit)) * tex->width);
	if((ray->wall_side == 0 && ray->dir.x > 0) || (ray->wall_side == 1 && ray->dir.y < 0))
		x_pos = tex->width - x_pos -  1;
	return(x_pos);
}

void paint_texture(t_player *player, t_ray *ray, mlx_texture_t *tex, int x)
{
	t_ivector	vtex;
	double		tex_pos;
	double		tex_step;
	int			i;

	vtex.x = get_x_pos(player, ray, tex);
	tex_step = tex->height / ray->proj_wall_height;
	tex_pos = (ray->wall_start - HEIGHT / 2 + ray->proj_wall_height / 2) * tex_step;
	i = ray->wall_start;
	while(i < ray->wall_end)
	{
		if(i >= 0)
		{
			vtex.y = (int)tex_pos % tex->height;
			//printf("i: %d, x: %d, vtex.y: %d, vtex.x: %d\n", i, x, vtex.y, vtex.x);
			/* if(player->img->pixels[(WIDTH * i + x) * 4] && tex->pixels[(tex->width * vtex.y + vtex.x) * 4]) */
			
				ft_memcpy(&player->img->pixels[(WIDTH * i + x) * 4], &tex->pixels[(tex->width * vtex.y + vtex.x) * 4], 4);
			tex_pos += tex_step;
		}
		i++;
	}
}

void paint_background(t_player *player, t_ray *ray, int x)
{
	int	i;

	i = 0;
	while(i < HEIGHT)
	{
		if(i < ray->wall_start + 1)
			draw_pixel(player->img, x, i, CEILING);
		else if (i > ray->wall_end - 1)
			draw_pixel(player->img, x, i, FLOOR);
		i++;
	}
}


uint32_t get_wall_color(t_player *player, t_ray *ray)
{
	uint32_t wall_color;

	wall_color = WALL;
	if (get_orientation(ray, player) == NORTH)
		wall_color = 0x8CB7DA;
	else if (get_orientation(ray, player) == SOUTH)
		wall_color = 0x00FF00FF;
	else if (get_orientation(ray, player) == WEST)
		wall_color = 0x0000FFFF;
	else if (get_orientation(ray, player) == EAST)
		wall_color = 0xF5F327CC;
	return (wall_color);
}