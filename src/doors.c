#include "../include/cub3d.h"

void cast_door_ray(t_player *player, t_data *data, double angle)
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
		if(data->map->map[(int)ray->interception.y][(int)ray->interception.x] = CLOSED_DOOR)
			data->map->map[(int)ray->interception.y][(int)ray->interception.x] = OPEN_DOOR;
	}
	free(ray);
}