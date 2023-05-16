#include "../include/cub3d.h"

int	wall_collision(char **map, double x, double y)
{
	if(map[(int)(y + 0.1)][(int)(x + 0.1)] == 0
		&& map[(int)(y - 0.1)][(int)(x - 0.1)] == 0
		&& map[(int)(y - 0.1)][(int)(x + 0.1)] == 0
		&& map[(int)(y + 0.1)][(int)(x - 0.1)] == 0)
		return (0);
	else
		return (1);
}

void move_down(t_data *data, double tmp_x, double tmp_y)
{
	double radians;
	double dx;
	double dy;

	radians = data->player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x -= dx * PLAYER_SPEED;
	tmp_y -= dy * PLAYER_SPEED;
	if(!wall_collision(data->map->map, tmp_x, tmp_y))
	{
		data->player->p_start.x = tmp_x;
		data->player->p_start.y = tmp_y;
	}
}

void move_up(t_data *data, double tmp_x, double tmp_y)
{
	double radians;
	double dx;
	double dy;

	radians = data->player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x += dx * PLAYER_SPEED;
	tmp_y += dy * PLAYER_SPEED;
	if(!wall_collision(data->map->map, tmp_x, tmp_y))
	{
		data->player->p_start.x = tmp_x;
		data->player->p_start.y = tmp_y;
	}
}

void move_left(t_data *data, double tmp_x, double tmp_y)
{
	double radians;
	double dx;
	double dy;

	radians = data->player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x += dy * PLAYER_SPEED;
	tmp_y -= dx * PLAYER_SPEED;
	if(!wall_collision(data->map->map, tmp_x, tmp_y))
	{
		data->player->p_start.x = tmp_x;
		data->player->p_start.y = tmp_y;
	}
}

void move_right(t_data *data, double tmp_x, double tmp_y)
{
	double radians;
	double dx;
	double dy;

	radians = data->player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x -= dy * PLAYER_SPEED;
	tmp_y += dx * PLAYER_SPEED;
	if(!wall_collision(data->map->map, tmp_x, tmp_y))
	{
		data->player->p_start.x = tmp_x;
		data->player->p_start.y = tmp_y;
	}
}

void move_player(t_data *data, keys_t key)
{
	double tmp_x;
	double tmp_y;

	tmp_x = data->player->p_start.x;
	tmp_y = data->player->p_start.y;
	if(key == MLX_KEY_UP)
		move_up(data, tmp_x, tmp_y);
	if(key == MLX_KEY_DOWN)
		move_down(data, tmp_x, tmp_y);
	if(key == MLX_KEY_LEFT)
		move_left(data, tmp_x, tmp_y);
	if(key == MLX_KEY_RIGHT)
		move_right(data, tmp_x, tmp_y);
}

void check_mouse_pos(t_data *data)
{
	static int x = WIDTH / 2;
	int new_x;
	int y;

	y = HEIGHT / 2;
	mlx_get_mouse_pos(data->mlx, &new_x, &y);
	if(x > new_x)
		data->player->angle -= ROTATION_SPEED;
	else if(x < new_x)
		data->player->angle += ROTATION_SPEED;
	x = new_x;
	if(abs(new_x - WIDTH / 2) > MOUSE_SENSITIVITY)
    {
        mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
        x = WIDTH / 2;
    }
}

void my_loop_hook(void *param)
{
	t_data *data;
	
	data = (t_data *)param;
	if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		move_player(data, MLX_KEY_RIGHT);
		if(data->player->p_start.x > data->map->max_width)
			data->player->p_start.x = data->map->max_width - 0.001;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		move_player(data, MLX_KEY_LEFT);
		if(data->player->p_start.x < 0)
			data->player->p_start.x = 0;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		move_player(data, MLX_KEY_DOWN);
		if(data->player->p_start.y > HEIGHT)
			data->player->p_start.y = data->map->max_height - 0.001;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		move_player(data, MLX_KEY_UP);	
		if(data->player->p_start.y < 0)
			data->player->p_start.y = 0;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player->angle += ROTATION_SPEED;
		if(data->player->angle > 360.0)
			data->player->angle -= 360;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player->angle -= ROTATION_SPEED;
		if(data->player->angle < 0)
			data->player->angle += 360;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if(mlx_is_key_down(data->mlx, MLX_KEY_W))
		cast_door_ray(data->player, data, data->player->angle);
	check_mouse_pos(data);
	draw_fov(data->player, data);
}
