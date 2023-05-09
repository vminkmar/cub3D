#include "../include/cub3d.h"

t_wall_orientation get_orientation(t_ray *ray)
{
	double	dx;
	double	dy;

	dx = player->p_start.x - ray->interception.x;
	dy = player->p_start.y - ray->interception.y;

	if(fabs(ray->dir.x) > fabs(ray->dir.y))
	{
		if (ray->dir.x > 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if(ray->dir.y >0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

uint32_t get_wall_color(t_ray *ray)
{
	uint32_t wall_color;

	wall_color = WALL;
	if (get_orientation(ray) == NORTH)
		wall_color = 0xFF0000FF;
	else if (get_orientation(ray) == SOUTH)
		wall_color = 0x00FF00FF;
	else if (get_orientation(ray) == WEST)
		wall_color = 0x0000FFFF;
	else if (get_orientation(ray) == EAST)
		wall_color = 0xFFFFFF00;
	return (wall_color);
}