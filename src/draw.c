/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:26:17 by mgraefen          #+#    #+#             */
/*   Updated: 2023/05/05 09:48:40 by mgraefen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
#define BPP sizeof(int32_t)

void draw_map(mlx_image_t *img, int map[][6]);
void	draw_one_stripe(t_player *player, double distance, int x);

void draw_square(mlx_image_t *img, int x, int y, uint32_t color)
{
	int new_x = x;
	int new_y = y;
	int count_x;
	int count_y;

	count_y = 0;
	while(count_y < HEIGHT / 6)
	{
		new_x = x;
		count_x = 0;
		while(count_x < WIDTH / 6)
		{
			mlx_put_pixel(img, new_x, new_y, color);
			new_x++;
			count_x++;
		}
		new_y++;
		count_y++;
	}
}

void	draw_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < WIDTH && x > 0 && y < HEIGHT && y > 0)
		mlx_put_pixel(img, x, y, color);
}

double angle_update_delta(t_coords dim, t_player *player, double dx, double dy, double angle)
{
	double	radius;
	double	new_delta;
	double	new_dim;
	
	radius = sqrt((dx * dx) + (dy * dy));
	if (dim == x_dim)
	{
		new_dim = player->x + radius * cos(angle);
		new_delta = new_dim - player->x;
	}
	if (dim == y_dim)
	{
		new_dim = player->y + radius * sin(angle);
		new_delta = new_dim - player->y;
	}
	return (new_delta);
}

int stop_line_drawing(t_player *player, double pix_y, double pix_x)
{
	int i;
    int j;
	
	i = (int)pix_y / (HEIGHT / 6);
    j = (int)pix_x / (WIDTH / 6);
	if(i > 5 || j > 5)
		return(0);
	if (player->map[i][j] == 1)
        return (1);
	return (0);
}

double distance_to_plain(double distance, double angle, double player_angle)
{
    double diff_angle = angle - player_angle;
    double perp_distance = distance * cos(diff_angle);
    return fabs(perp_distance);
}

double distance_to_wall(int put_pix, int origin_put_pix, double angle, double player_angle)
{
	double distance;

	distance = (double)origin_put_pix - (double)put_pix;
	//printf("Distance to Wall: %i\n", distance_to_wall);
	distance = distance_to_plain(distance, angle, player_angle);
	return (fabs(distance));
}

void	cast_ray(t_player *player, double angle)
{
	double	dx;
	double	dy;
	double	pix_x;
	double	pix_y;
	int		put_pix;
	int		origin_put_pix;
	uint32_t color;

	dx = WIDTH;
	dy = HEIGHT;
	double radians = angle * (M_PI / 180.0);
	//double radians_player = player->angle * (M_PI / 180.0);
	dx = angle_update_delta(x_dim, player, dx, dy, radians);
	dy = angle_update_delta(y_dim, player, dx, dy, radians);
	put_pix = sqrt((dx * dx) + (dy * dy));
	origin_put_pix = put_pix;
	dx /= put_pix;
	dy /= put_pix;
	pix_x = player->x;
	pix_y = player->y;
	color = 0xFF00FF;
	while (put_pix)
	{
        if (stop_line_drawing(player, pix_y, pix_x))
            break;
		draw_pixel(player->img, pix_x, pix_y, color);
		pix_x = pix_x + dx;
		pix_y = pix_y + dy;
		put_pix--;
	}
	//draw_one_stripe(player, distance_to_wall(put_pix, origin_put_pix, radians, radians_player));
}

void cast_dda_ray(t_player *player, double angle)
{
	double	ray_dir_y;
	double	ray_dir_x;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

	map_x = (int)player->x;
	map_y = (int)player->y;
	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);
	angle = angle * (M_PI / 180.0);
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	hit = 0;
	
	if(ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (player->x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - player->x) * delta_dist_x;
	}
	if(ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (player->y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - player->y) * delta_dist_y;
	}
	while(!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_x < 0 || map_x >= 6 || map_y < 0 || map_y >= 6)
			break;
		draw_pixel(player->img, map_x, map_y, 0xFF0000FF);
		if(player->map[map_y][map_x] > 0)
			hit = 1;
	}
	if(!side)
		perp_wall_dist = (map_x - player->x + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - player->y + (1 - step_y) / 2) / ray_dir_y;
	//draw_one_stripe(player, perp_wall_dist, i);
}

void	draw_one_stripe(t_player *player, double distance, int x)
{
	int y;
	int wall_start;
	int	wall_end;
	int proj_wall_height;
	uint32_t color;

	y = 0;
	if(distance <= 0)
		return ;
	proj_wall_height = (HEIGHT / distance);
    wall_start = (HEIGHT - proj_wall_height) / 2;
    wall_end = wall_start + proj_wall_height;

    while (y < HEIGHT)
    {
        if (y < wall_start)
            color = CEILING;
        else if (y < wall_end)
            color = WALL;
        else
            color = FLOOR;
		if(x > 0 && x < WIDTH && (y > 0 && y < HEIGHT))
        	mlx_put_pixel(player->img, x, y, color);
		y++;
    }
}

void	draw_fov(t_player *player)
{
	double	current_angle;
	double	end_angle;
	double	step;
	int		i;
	
	i = 0;
	current_angle = player->angle - (player->fov / 2);
	end_angle = player->angle + (player->fov / 2);
	step = player->fov / (double)WIDTH;
	while (current_angle < end_angle)
	{
		cast_dda_ray(player, current_angle);
		current_angle += step;
		i++;
	} 
}

void thickenize_pixel(t_player *player, double x, double y, uint32_t color)
{
    double i;
	double j;
	
    i = -3;
    while (i <= 3)
    {
        j = -3;
        while (j <= 3)
        {
            if (i == 0 && j == 0)
			{
				if (y + j) 
                	mlx_put_pixel(player->img, x + i, y + j, color);
			}
            else
			{
				if(y + j)
				{
                	mlx_put_pixel(player->img, x + i, y + j, color);
				}
			}
            j++;
        }
        i++;
    }
/* 	(void)x;
	(void)y;
	(void)color; */
	//draw_fov(player);
	cast_ray(player, player->angle);
}

void my_loop_hook(void *param)
{
	t_player *player;
	
	player = (t_player *)param;
	draw_map(player->img, player->map);
	if(mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
	{
		thickenize_pixel(player, player->x, player->y, 0xFFFFFFFF);
		player->x += 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
	{
		thickenize_pixel(player, player->x, player->y, 0xFFFFFFFF);
		player->x -= 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_DOWN))
	{
		thickenize_pixel(player, player->x, player->y, 0xFFFFFFFF);
		player->y += 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_UP))
	{
		thickenize_pixel(player, player->x, player->y, 0xFFFFFFFF);
		player->y -= 5;
		if(player->y <= 0)
			player->y = 1;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_D))
	{
		thickenize_pixel(player, player->x, player->y, 0xFFFFFFFF);
		player->angle += 1;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_A))
	{
		thickenize_pixel(player, player->x, player->y, 0xFFFFFFFF);
		player->angle -= 1;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(player->mlx);
	thickenize_pixel(player, player->x, player->y, 0x00FF0000);
}

void draw_map(mlx_image_t *img, int map[][6])
{
	int x = 0;
	int y = 0;
	int	i;
	int	j;
	j = 0;
	i = 0;
	while(i < 4)
	{
		j = 0;
		x = 0;
		while(j < 4)
		{
			if(map[i][j])
				draw_square(img, x, y, 0x000000FF);
			else
				draw_square(img, x, y, 0xFFFFFFFF);

			j++;
			x += WIDTH / 4;
		}
		y += HEIGHT / 4;
		i++;
	}
}

int32_t	main(void)
{
	
	t_player *player;
	
	player = malloc(sizeof(t_player));
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = 0;
	player->fov = 45;
	int map[6][6] =
	{ 	{1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1}
	};
	
	/* ft_memcpy(player->map, map, sizeof(map)); */
	for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
        player->map[i][j] = map[i][j];
    }
}

	
    // Init mlx with a canvas size of 256x256 and the ability to resize the window.
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
    if (!mlx) exit(EXIT_FAILURE);
	player->mlx = mlx;

	
    // Create a 128x128 image.
    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	player ->img = img;

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    memset(img->pixels, 255, img->width * img->height * BPP);

    // Draw the image at coordinate (0, 0).
	mlx_image_to_window(mlx, img, 0, 0);
	//draw_stripe(player);
	//draw_map(img, player->map);
	mlx_loop_hook(mlx, &my_loop_hook, player);
    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}

