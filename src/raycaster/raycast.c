#include "../../include/cub3d.h"

void	get_stepsize(t_ray *ray)
{
	ray->step_size.x = fabs(1 / ray->dir.x + EPSILON);
	ray->step_size.y = fabs(1 / ray->dir.y + EPSILON);
}

void	init_ray(t_player *player, t_ray *ray, double angle)
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

void	cast_ray(t_player *player, t_data *data, double angle, int x)
{	
	t_ray		*ray;
	int			hit;
	float		max_distance;

	max_distance = sqrt(data->map->max_height * data->map->max_height)
		+ (data->map->max_width * data->map->max_width);
	hit = 0;
	ray = malloc(sizeof(t_ray));
	init_ray(player, ray, angle);
	get_stepsize(ray);
	get_steps(ray);
	while (!hit && ray->distance + EPSILON < max_distance)
		wall_hit(data, ray, &hit);
	if (hit)
	{
		set_wall(ray, player, angle);
/* 		if (data->map->map[(int)ray->interception.y][(int)ray->interception.x] ==  WALL)
			printf("WALL\n");
		if (data->map->map[(int)ray->interception.y][(int)ray->interception.x] ==  CLOSED_DOOR)
			printf("DOOR\n"); */
		printf("INTER Y:%f\n", ray->interception.y);
		printf("INTER X:%f\n", ray->interception.x);
		printf("INTER I Y:%i\n", (int)ray->interception.y);
		printf("INTER I X:%i\n", (int)ray->interception.x);
		paint_background(data, ray, x);
		paint_texture(data, ray, x);
	}
	free(ray);
}

void	draw_fov(t_player *player, t_data *data)
{
	double	current_angle;
	double	step;
	int		x;

	current_angle = player->angle - (player->fov / 2);
	step = player->fov / (double)WIDTH;
	x = 0;
	data->map->color_floor = 0xFF0000FF;
	data->map->color_ceiling = 0x00FF00FF;
	while (x < WIDTH)
	{
		cast_ray(player, data, current_angle + x * step, x);
		x++;
	}
}

void	raycaster(t_data *data)
{
	memset(data->img->pixels, 255, data->img->width * data->img->height * BPP);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap_img, 10, 10);
	mlx_loop_hook(data->mlx, &my_loop_hook, data);
	mlx_key_hook(data->mlx, interac_hook, data);
	mlx_loop(data->mlx);
}
