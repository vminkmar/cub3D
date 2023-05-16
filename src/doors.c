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
		printf("%f\n", ray->distance);
		ray->interception.x = ray->start.x + ray->dir.x * ray->distance;
		ray->interception.y = ray->start.y + ray->dir.y * ray->distance;
		printf("%f\n", ray->interception.y);
		printf("%f\n", ray->interception.x);
		if(data->map->map[(int)ray->interception.y][(int)ray->interception.x] == CLOSED_DOOR && ray->distance <= 1)
		{
			printf("HIT\n");
			data->map->map[(int)ray->interception.y][(int)ray->interception.x] = OPEN_DOOR;
		}
		/* else if (data->map->map[(int)ray->interception.y][(int)ray->interception.x] == OPEN_DOOR && ray->distance >= 0.1)
			data->map->map[(int)ray->interception.y][(int)ray->interception.x] = CLOSED_DOOR; */
	}
	free(ray);
}