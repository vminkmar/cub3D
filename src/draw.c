#include "../include/cub3d.h"

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
#define BPP sizeof(int32_t)

void	draw_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
		mlx_put_pixel(img, x, y, color);
}

void get_steps(t_ray *ray)
{
    if(ray->dir.x < 0)
    {
        ray->step.x = -1;
        ray->length.x = fabs((ray->start.x - (float)ray->map_check.x) * ray->step_size.x);
    }
    else
    {
        ray->step.x = 1;
        ray->length.x = fabs(((float)ray->map_check.x + 1 - ray->start.x) * ray->step_size.x);
    }
    if(ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->length.y = fabs((ray->start.y - (float)ray->map_check.y) * ray->step_size.y);
    }
    else
    {
        ray->step.y = 1;
        ray->length.y = fabs(((float)ray->map_check.y + 1 - ray->start.y) * ray->step_size.y);
    }
}

void get_stepsize(t_ray *ray)
{
	ray->step_size.x = fabs(1 / ray->dir.x + EPSILON);
    ray->step_size.y = fabs(1 / ray->dir.y + EPSILON);
}

void wall_hit(t_data *data, t_ray *ray, int *hit)
{
	if(ray->length.x < ray->length.y)
	{
		ray->wall_side = 0;
		ray->map_check.x += ray->step.x;
		ray->distance = ray->length.x;
		ray->length.x += ray->step_size.x;
	}
	else
	{
		ray->wall_side = 1;
		ray->map_check.y += ray->step.y;
		ray->distance = ray->length.y;
		ray->length.y += ray->step_size.y;
	}
/* 	if((ray->map_check.x >= 0 && ray->map_check.x < GRID_WIDTH) && (ray->map_check.y >= 0 && ray->map_check.y < GRID_HEIGHT))
	{ */
	if(data->map->map[ray->map_check.y][ray->map_check.x] == 1)
			*hit = 1;
	}
/* } */

void init_ray(t_player *player, t_ray *ray, double angle)
{
	ray->length.x = 0;
	ray->length.y = 0;
	ray->start.x = player->p_start.x;
	ray->start.y = player->p_start.y;
	ray->map_check.x = (int)ray->start.x;
	ray->map_check.y = (int)ray->start.y;
	ray->dir = angle_to_vector(angle);
	ray->distance = 0;
	ray->proj_wall_height = 0;
	ray->wall_start = 0;
	ray->wall_end = 0;
	ray->wall_side = 0;
}

double distance_to_plane(double distance, double angle, double player_angle)
{
    double diff_angle;
	double perp_distance;

	diff_angle = (angle * (M_PI / 180.0)) - (player_angle * (M_PI / 180.0));
	perp_distance = distance * cos(diff_angle);
    return fabs(perp_distance);
}

void set_wall(t_ray *ray, t_player *player, double angle)
{
	ray->interception.x = ray->start.x + ray->dir.x * ray->distance;
	ray->interception.y = ray->start.y + ray->dir.y * ray->distance;
	ray->distance = distance_to_plane(ray->distance, angle, player->angle);
	ray->proj_wall_height = (int)HEIGHT / ray->distance;
	if (ray->wall_side == 0)
    	ray->distance = fabs(ray->length.x - ray->step_size.x);
	else
    	ray->distance = fabs(ray->length.y - ray->step_size.y);
	ray->wall_start = ((HEIGHT - ray->proj_wall_height) / 2);
	if(ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->wall_start + ray->proj_wall_height;
	if(ray->wall_end >= HEIGHT)
		ray->wall_end = HEIGHT;
}

void cast_ray(t_player *player, t_data *data, double angle, int x)
{	
	t_ray		*ray;
	int			hit;
	float		max_distance;
	
	max_distance = sqrt(data->map->max_height * data->map->max_height) + (data->map->max_width * data->map->max_width);
	hit = 0;
	ray = malloc(sizeof(t_ray));
	init_ray(player, ray, angle);
	get_stepsize(ray);
	get_steps(ray);
	while(!hit && ray->distance + EPSILON < max_distance)
		wall_hit(data, ray, &hit);
	if(hit)
	{
		set_wall(ray, player, angle);
		paint_background(data, ray, x);
		paint_texture(data, ray, x);
	}
	free(ray);
}

void	draw_fov(t_player *player, t_data *data)
{
	double	current_angle;
	double	end_angle;
	double	step;
	int		x;
	
	current_angle = player->angle - (player->fov / 2);
	end_angle = player->angle + (player->fov / 2);
	step = player->fov / (double)WIDTH;
	x = 0;
	//ft_bzero(data->img->pixels, WIDTH * HEIGHT * 4);
	data->map->color_floor = 0xFF0000FF;
	data->map->color_ceiling = 0x00FF00FF;
	while (x < WIDTH)
	{
		cast_ray(player, data, current_angle + x * step, x);
		x++;
	} 
}

void init_player(t_data *data)
{
	data->player->p_start.x = (double)data->map->max_width / 2;
	data->player->p_start.y = (double)data->map->max_height / 2;
	data->player->angle = 90;
	data->player->fov = 60;
}

void raycaster(t_data *data)
{
	memset(data->img->pixels, 255, data->img->width * data->img->height * BPP);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, &my_loop_hook, data);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
}
