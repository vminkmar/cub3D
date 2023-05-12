#include "../include/cub3d.h"

int	wall_collision(t_player *player, double x, double y)
{
	if(player->map[(int)(y + 0.1)][(int)(x + 0.1)] == 0
		&& player->map[(int)(y - 0.1)][(int)(x - 0.1)] == 0
		&& player->map[(int)(y - 0.1)][(int)(x + 0.1)] == 0
		&& player->map[(int)(y + 0.1)][(int)(x - 0.1)] == 0)
		return (0);
	else
		return (1);
}

void move_down(t_player *player, double tmp_x, double tmp_y)
{
	double radians;
	double dx;
	double dy;

	radians = player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x -= dx * PLAYER_SPEED;
	tmp_y -= dy * PLAYER_SPEED;
	if(!wall_collision(player, tmp_x, tmp_y))
	{
		player->p_start.x = tmp_x;
		player->p_start.y = tmp_y;
	}
}

void move_up(t_player *player, double tmp_x, double tmp_y)
{
	double radians;
	double dx;
	double dy;

	radians = player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x += dx * PLAYER_SPEED;
	tmp_y += dy * PLAYER_SPEED;
	if(!wall_collision(player, tmp_x, tmp_y))
	{
		player->p_start.x = tmp_x;
		player->p_start.y = tmp_y;
	}
}

void move_left(t_player *player, double tmp_x, double tmp_y)
{
	double radians;
	double dx;
	double dy;

	radians = player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x += dy * PLAYER_SPEED;
	tmp_y -= dx * PLAYER_SPEED;
	if(!wall_collision(player, tmp_x, tmp_y))
	{
		player->p_start.x = tmp_x;
		player->p_start.y = tmp_y;
	}
}

void move_right(t_player *player, double tmp_x, double tmp_y)
{
	double radians;
	double dx;
	double dy;

	radians = player->angle * (M_PI / 180.0);
	dx = cos(radians);
	dy = sin(radians);
	tmp_x -= dy * PLAYER_SPEED;
	tmp_y += dx * PLAYER_SPEED;
	if(!wall_collision(player, tmp_x, tmp_y))
	{
		player->p_start.x = tmp_x;
		player->p_start.y = tmp_y;
	}
}

void move_player(t_player *player, keys_t key)
{
	double tmp_x;
	double tmp_y;

	tmp_x = player->p_start.x;
	tmp_y = player->p_start.y;
	if(key == MLX_KEY_UP)
		move_up(player, tmp_x, tmp_y);
	if(key == MLX_KEY_DOWN)
		move_down(player, tmp_x, tmp_y);
	if(key == MLX_KEY_LEFT)
		move_left(player, tmp_x, tmp_y);
	if(key == MLX_KEY_RIGHT)
		move_right(player, tmp_x, tmp_y);
}

void check_mouse_pos(t_player *player)
{
	static int x = WIDTH / 2;
	int new_x;
	int y;

	y = HEIGHT / 2;
	mlx_get_mouse_pos(player->mlx, &new_x, &y);
	if(x > new_x)
		player->angle -= ROTATION_SPEED;
	else if(x < new_x)
		player->angle += ROTATION_SPEED;
	x = new_x;
	if(abs(new_x - WIDTH / 2) > MOUSE_SENSITIVITY)
    {
        mlx_set_mouse_pos(player->mlx, WIDTH / 2, HEIGHT / 2);
        x = WIDTH / 2;
    }
}

void my_loop_hook(void *param)
{
	t_player *player;
	
	player = (t_player *)param;
	if(mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
	{
		move_player(player, MLX_KEY_RIGHT);
		if(player->p_start.x > GRID_WIDTH)
			player->p_start.x = GRID_WIDTH - 0.001;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
	{
		move_player(player, MLX_KEY_LEFT);
		if(player->p_start.x < 0)
			player->p_start.x = 0;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_DOWN))
	{
		move_player(player, MLX_KEY_DOWN);
		if(player->p_start.y > HEIGHT)
			player->p_start.y = GRID_HEIGHT - 0.001;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_UP))
	{
		move_player(player, MLX_KEY_UP);	
		if(player->p_start.y < 0)
			player->p_start.y = 0;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_D))
	{
		player->angle += ROTATION_SPEED;
		if(player->angle > 360.0)
			player->angle -= 360;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_A))
	{
		player->angle -= ROTATION_SPEED;
		if(player->angle < 0)
			player->angle += 360;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(player->mlx);
	check_mouse_pos(player);
	draw_fov(player);
}
