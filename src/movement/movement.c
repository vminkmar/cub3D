#include "../../include/cub3d.h"

void	move_player(t_data *data, keys_t key)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = data->player->p_start.x;
	tmp_y = data->player->p_start.y;
	if (key == MLX_KEY_W)
		move_up(data, tmp_x, tmp_y);
	if (key == MLX_KEY_S)
		move_down(data, tmp_x, tmp_y);
	if (key == MLX_KEY_A)
		move_left(data, tmp_x, tmp_y);
	if (key == MLX_KEY_D)
		move_right(data, tmp_x, tmp_y);
}

void	check_mouse_pos(t_data *data)
{
	static int	x = WIDTH / 2;
	int			new_x;
	int			y;

	y = HEIGHT / 2;
	mlx_get_mouse_pos(data->mlx, &new_x, &y);
	if (x > new_x)
		data->player->angle -= ROTATION_SPEED;
	else if (x < new_x)
		data->player->angle += ROTATION_SPEED;
	x = new_x;
	if (abs(new_x - WIDTH / 2) > MOUSE_SENSITIVITY)
	{
		mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
		x = WIDTH / 2;
	}
}

void	key_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player->angle += ROTATION_SPEED;
		if (data->player->angle > 360.0)
			data->player->angle -= 360;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player->angle -= ROTATION_SPEED;
		if (data->player->angle < 0)
			data->player->angle += 360;
	}
}

void	key_directions(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		move_player(data, MLX_KEY_D);
		if (data->player->p_start.x > data->map->max_width)
			data->player->p_start.x = data->map->max_width - 0.001;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		move_player(data, MLX_KEY_A);
		if (data->player->p_start.x < 0)
			data->player->p_start.x = 0;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		move_player(data, MLX_KEY_S);
		if (data->player->p_start.y > HEIGHT)
			data->player->p_start.y = data->map->max_height - 0.001;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		move_player(data, MLX_KEY_W);
		if (data->player->p_start.y < 0)
			data->player->p_start.y = 0;
	}
}

void	my_loop_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	key_directions(data);
	key_rotation(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	check_mouse_pos(data);
	draw_fov(data->player, data);
	data->framecount++;
	if (data->framecount == LONG_MAX)
		data->framecount = 1;
}
