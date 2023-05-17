#include "../include/cub3d.h"

void cast_door_ray(t_data *data, t_player *player)
{
    t_ray *ray;

	ray = malloc(sizeof(t_ray));
	init_ray(player, ray, player->angle);
	ray->start.x = player->p_start.x;
	ray->start.y = player->p_start.y;
    while (ray->start.x >= 0 && ray->start.x < data->map->max_width && ray->start.y >= 0 && ray->start.y < data->map->max_height)
	{
		int map_x = (int)ray->start.x;
        int map_y = (int)ray->start.y;
        if (data->map->map[map_y][map_x] == CLOSED_DOOR || data->map->map[map_y][map_x] == OPEN_DOOR)
		{
			ray->distance = sqrt(pow(ray->start.x - player->p_start.x, 2) + pow(ray->start.y - player->p_start.y, 2));
			if(data->map->map[map_y][map_x] == CLOSED_DOOR && ray->distance < 1.5)
				data->map->map[map_y][map_x] = OPEN_DOOR;
			else if(data->map->map[map_y][map_x] == OPEN_DOOR && ray->distance >= 0.5)
				data->map->map[map_y][map_x] = CLOSED_DOOR;
            break;
        }
        ray->start.x += ray->dir.x;
        ray->start.y += ray->dir.y;
    }
	free(ray);
}