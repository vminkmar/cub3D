#include "../../include/cub3d.h"

void	interac_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		cast_door_ray(data, data->player);
}

void	open_close_door(t_data *data, t_ray *ray, int map_x, int map_y)
{
	ray->distance = sqrt(pow(ray->start.x - data->player->p_start.x, 2)
			+ pow(ray->start.y - data->player->p_start.y, 2));
	if (data->map->map[map_y][map_x] == CLOSED_DOOR
		&& ray->distance < 1.5)
			data->map->map[map_y][map_x] = OPEN_DOOR;
	else if (data->map->map[map_y][map_x] == OPEN_DOOR
		&& ray->distance >= 0.5)
			data->map->map[map_y][map_x] = CLOSED_DOOR;
}

void	cast_door_ray(t_data *data, t_player *player)
{
	t_ray	*ray;
	int		map_x;
	int		map_y;

	ray = malloc(sizeof(t_ray));
	init_ray(player, ray, player->angle);
	ray->start.x = player->p_start.x;
	ray->start.y = player->p_start.y;
	while (ray->start.x >= 0 && ray->start.x < data->map->max_width
		&& ray->start.y >= 0 && ray->start.y < data->map->max_height)
	{
		map_x = (int)ray->start.x;
		map_y = (int)ray->start.y;
		if (data->map->map[map_y][map_x] == CLOSED_DOOR
			|| data->map->map[map_y][map_x] == OPEN_DOOR)
		{
			open_close_door(data, ray, map_x, map_y);
			break ;
		}
		ray->start.x += ray->dir.x;
		ray->start.y += ray->dir.y;
	}
	free(ray);
}
