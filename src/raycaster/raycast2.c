#include "../../include/cub3d.h"

void	wall_hit(t_data *data, t_ray *ray, int *hit)
{
	if (ray->length.x < ray->length.y)
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
	if (data->map->map[ray->map_check.y][ray->map_check.x] == WALL
		|| data->map->map[ray->map_check.y][ray->map_check.x] == CLOSED_DOOR)
			*hit = 1;
}

double	distance_to_plane(double distance, double angle, double player_angle)
{
	double	diff_angle;
	double	perp_distance;

	diff_angle = (angle * (M_PI / 180.0)) - (player_angle * (M_PI / 180.0));
	perp_distance = distance * cos(diff_angle);
	return (fabs(perp_distance));
}

void	set_wall(t_ray *ray, t_player *player, double angle)
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
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->wall_start + ray->proj_wall_height;
	if (ray->wall_end >= HEIGHT)
		ray->wall_end = HEIGHT;
}

void	get_steps(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->length.x = fabs((ray->start.x - (float)ray->map_check.x)
				* ray->step_size.x);
	}
	else
	{
		ray->step.x = 1;
		ray->length.x = fabs(((float)ray->map_check.x + 1 - ray->start.x)
				* ray->step_size.x);
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->length.y = fabs((ray->start.y - (float)ray->map_check.y)
				* ray->step_size.y);
	}
	else
	{
		ray->step.y = 1;
		ray->length.y = fabs(((float)ray->map_check.y + 1 - ray->start.y)
				* ray->step_size.y);
	}
}
