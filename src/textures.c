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