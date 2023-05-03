/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:26:17 by mgraefen          #+#    #+#             */
/*   Updated: 2023/05/03 16:40:36 by mgraefen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
#define BPP sizeof(int32_t)

void draw_map(mlx_image_t *img, int map[][4]);

void draw_square(mlx_image_t *img, int x, int y, uint32_t color)
{
	int new_x = x;
	int new_y = y;
	int count_x;
	int count_y;

	count_y = 0;
	while(count_y < HEIGHT / 4)
	{
		new_x = x;
		count_x = 0;
		while(count_x < WIDTH / 4)
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
	
	i = (int)pix_y / (HEIGHT / 4);
    j = (int)pix_x / (WIDTH / 4);

	if (player->map[i][j] == 1)
        return (1);
	return (0);
}

void distance_to_wall(int put_pix, int origin_put_pix)
{
	int distance_to_wall;

	distance_to_wall = origin_put_pix - put_pix;
	printf("Distance to Wall: %i\n", distance_to_wall);
}

void	draw_line(t_player *player, uint32_t color, double angle)
{
	double	dx;
	double	dy;
	double	pix_x;
	double	pix_y;
	int		put_pix;
	int		origin_put_pix;

	dx = WIDTH;
	dy = HEIGHT;
	double radians = angle * (M_PI / 180.0);
	dx = angle_update_delta(x_dim, player, dx, dy, radians);
	dy = angle_update_delta(y_dim, player, dx, dy, radians);
	put_pix = sqrt((dx * dx) + (dy * dy));
	origin_put_pix = put_pix;
	dx /= put_pix;
	dy /= put_pix;
	pix_x = player->x;
	pix_y = player->y;
	while (put_pix)
	{
        if (stop_line_drawing(player, pix_y, pix_x))
            break;
		draw_pixel(player->img, pix_x, pix_y, color);
		pix_x = pix_x + dx;
		pix_y = pix_y + dy;
		put_pix--;
	}
	//distance_to_wall(put_pix, origin_put_pix);
}

void	draw_stripe(t_player *player)
{
	int	height_c;
	int	height_w;
	int	height_f;

	int x;
	int y;

	x = 0;
	y = 0;
	height_c = 0;
	height_w = 0 + HEIGHT / 3;
	height_f = height_w + HEIGHT / 3;
	while(x < WIDTH)
	{
		y = 0;
		while(y < HEIGHT)
		{
			while(y < height_w)
			{
				draw_pixel(player->img, x, y, CEILING);
				y++;
			}
			while(y < height_f)
			{
				draw_pixel(player->img, x, y, WALL);
				y++;
			}
			while(y < HEIGHT)
			{
				draw_pixel(player->img, x, y, FLOOR);
				y++;
			}
		}
		x++;
	}
	
}

void	draw_fov(t_player *player)
{
	double	current_angle;
	double	end_angle;
	double	step;
	
	current_angle = player->angle - (player->fov / 2);
	end_angle = player->angle + (player->fov / 2);
	step = player->fov / (double)WIDTH;
	while (current_angle < end_angle)
	{
		draw_line(player, 0xFF0000FF, current_angle);
		current_angle += step;
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
	draw_fov(player);
	draw_line(player, 0xFFFF00FF, player->angle);
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

void draw_map(mlx_image_t *img, int map[][4])
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
	player->fov = 60;
	int map[4][4] =
	{ 	{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 0},
		{1, 0, 1, 0}
	};
	
	ft_memcpy(player->map, map, sizeof(map));
	
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
	draw_stripe(player);
	//draw_map(img, player->map);
	//mlx_loop_hook(mlx, &my_loop_hook, player);
    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}

