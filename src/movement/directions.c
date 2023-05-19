#include "../../include/cub3d.h"

int	wall_collision(char **map, double x, double y)
{
	if (map[(int)(y + 0.1)][(int)(x + 0.1)] <= WALKABLE
		&& map[(int)(y - 0.1)][(int)(x - 0.1)] <= WALKABLE
		&& map[(int)(y - 0.1)][(int)(x + 0.1)] <= WALKABLE
		&& map[(int)(y + 0.1)][(int)(x - 0.1)] <= WALKABLE)
		return (0);
	else
		return (1);
}

void	move_down(t_data *data, double tmp_x, double tmp_y)
{
	double	radians;
	double	dx;
	double	dy;

	radians = data->player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x -= dx * PLAYER_SPEED;
	tmp_y -= dy * PLAYER_SPEED;
	if (!wall_collision(data->map->map, tmp_x, tmp_y))
	{
		data->player->p_start.x = tmp_x;
		data->player->p_start.y = tmp_y;
	}
}

void	move_up(t_data *data, double tmp_x, double tmp_y)
{
	double	radians;
	double	dx;
	double	dy;

	radians = data->player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x += dx * PLAYER_SPEED;
	tmp_y += dy * PLAYER_SPEED;
	if (!wall_collision(data->map->map, tmp_x, tmp_y))
	{
		data->player->p_start.x = tmp_x;
		data->player->p_start.y = tmp_y;
	}
}

void	move_left(t_data *data, double tmp_x, double tmp_y)
{
	double	radians;
	double	dx;
	double	dy;

	radians = data->player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x += dy * PLAYER_SPEED;
	tmp_y -= dx * PLAYER_SPEED;
	if (!wall_collision(data->map->map, tmp_x, tmp_y))
	{
		data->player->p_start.x = tmp_x;
		data->player->p_start.y = tmp_y;
	}
}

void	move_right(t_data *data, double tmp_x, double tmp_y)
{
	double	radians;
	double	dx;
	double	dy;

	radians = data->player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x -= dy * PLAYER_SPEED;
	tmp_y += dx * PLAYER_SPEED;
	if (!wall_collision(data->map->map, tmp_x, tmp_y))
	{
		data->player->p_start.x = tmp_x;
		data->player->p_start.y = tmp_y;
	}
}