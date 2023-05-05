/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:26:17 by mgraefen          #+#    #+#             */
/*   Updated: 2023/05/05 16:41:11 by mgraefen         ###   ########.fr       */
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

/* double angle_update_delta(t_coords dim, t_player *player, double dx, double dy, double angle)
{
	double	radius;
	double	new_delta;
	double	new_dim;
	
	radius = sqrt((dx * dx) + (dy * dy));
	if (dim == x_dim)
	{
		new_dim = player->p_start.x + radius * cos(angle);
		new_delta = new_dim - player->p_start.x;
	}
	if (dim == y_dim)
	{
		new_dim = player->p_start.y + radius * sin(angle);
		new_delta = new_dim - player->p_start.y;
	}
	return (new_delta);
} */

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

void	get_steps(t_ray *ray)
{
	if(ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->length.x = (ray->start.x - (float)ray->map_check.x) * ray->step_size.x;
	}
	else
	{
		ray->step.x = 1;
		ray->length.x = ((float)ray->map_check.x + 1) - (float)ray->start.x * ray->step_size.x;
	}
	if(ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->length.y = (ray->start.y - (float)ray->map_check.y) * ray->step_size.y;
	}
	else
	{
		ray->step.y = 1;
		ray->length.y = ((float)ray->map_check.y + 1) - (float)ray->start.y * ray->step_size.y;
	}
}

t_fvector	angle_to_vector(double angle)
{
	t_fvector vector;
	
	double radians;
	
	radians = angle * (M_PI / 180.0);
    vector.x = cos(radians);
    vector.y = sin(radians);
	return(vector);
}

void get_stepsize(t_ray *ray)
{
	ray->step_size.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	ray->step_size.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
}

void wall_hit(t_player *player, t_ray *ray, float *distance, int *hit)
{
	if(ray->length.x < ray->length.y)
	{
		ray->map_check.x += ray->step.x;
		*distance = ray->length.x;
		ray->length.x += ray->step_size.x;
	}
	else
	{
		ray->map_check.y += ray->step.y;
		*distance = ray->length.y;
		ray->length.y += ray->step_size.y;
	}
	printf("map_check: (%d, %d)\n", ray->map_check.x, ray->map_check.y);
	if((ray->map_check.x > 0 && ray->map_check.x < 6) && (ray->map_check.y > 0 && ray->map_check.y < 6))
	{
		if(player->map[ray->map_check.y][ray->map_check.x] == 1)
			*hit = 1;
	}
}

void draw_line_to_interception(t_player *player, uint32_t color, t_fvector start, t_fvector interception) {
    int total_steps = 100;
    for (int current_step = 0; current_step <= total_steps; current_step++) {
        double t = (double)current_step / (double)total_steps;
        t_fvector point;
        point.x = start.x + (interception.x - start.x) * t;
        point.y = start.y + (interception.y - start.y) * t;
        
        draw_pixel(player->img, (int)point.x, (int)point.y, color);
    }
}

void cast_ray(t_player *player, uint32_t color, double angle)
{	
	t_ray	*ray;
	int		hit;
	float	distance;
	float	max_distance;
	
	max_distance = WIDTH;
	distance = 0;
	hit = 0;
	ray = NULL;
	ray = malloc(sizeof(t_ray));
	ray->start.x = player->p_start.x;
	ray->start.y = player->p_start.y;
	ray->dir = angle_to_vector(angle);
	get_stepsize(ray);
	ray->map_check.x = (int)ray->start.x;
	ray->map_check.y = (int)ray->start.y;
	get_steps(ray);
	while(!hit && distance < max_distance)
	{
		wall_hit(player, ray, &distance, &hit);
		printf("distance: %f, hit: %d, map_check: (%d, %d)\n", distance, hit, ray->map_check.x, ray->map_check.y);
	}
	printf("Exited loop: distance: %f, hit: %d\n", distance, hit);
	if(hit)
	{
		printf("hi\n");
		ray->interception.x = ray->start.x + ray->dir.x * distance;
		ray->interception.y = ray->start.y + ray->dir.y * distance;
		draw_line_to_interception(player, color, ray->start, ray->interception);
		//draw_pixel(player->img, (int)ray->interception.x, (int)ray->interception.y, color);
	}
}

/* void	draw_line(t_player *player, uint32_t color, double angle)
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
	pix_x = player->p_start.x;
	pix_y = player->p_start.y;
	while (put_pix)
	{
        if (stop_line_drawing(player, pix_y, pix_x))
            break;
		draw_pixel(player->img, pix_x, pix_y, color);
		pix_x = pix_x + dx;
		pix_y = pix_y + dy;
		put_pix--;
	}
	distance_to_wall(put_pix, origin_put_pix);
} */

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
		cast_ray(player, 0xFF0000FF, current_angle);
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
                	draw_pixel(player->img, x + i, y + j, color);
			}
            else
			{
				if(y + j)
				{
                	draw_pixel(player->img, x + i, y + j, color);
				}
			}
            j++;
        }
        i++;
    }
	draw_fov(player);
	cast_ray(player, 0xFFFF00FF, player->angle);
}

void my_loop_hook(void *param)
{
	t_player *player;
	
	player = (t_player *)param;
	draw_map(player->img, player->map);
	if(mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
	{
		thickenize_pixel(player, player->p_start.x, player->p_start.y, 0xFFFFFFFF);
		player->p_start.x += 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
	{
		thickenize_pixel(player, player->p_start.x, player->p_start.y, 0xFFFFFFFF);
		player->p_start.x -= 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_DOWN))
	{
		thickenize_pixel(player, player->p_start.x, player->p_start.y, 0xFFFFFFFF);
		player->p_start.y += 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_UP))
	{
		thickenize_pixel(player, player->p_start.x, player->p_start.y, 0xFFFFFFFF);
		player->p_start.y -= 5;
		if(player->p_start.y <= 0)
			player->p_start.y = 1;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_D))
	{
		thickenize_pixel(player, player->p_start.x, player->p_start.y, 0xFFFFFFFF);
		player->angle += 1;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_A))
	{
		thickenize_pixel(player, player->p_start.x, player->p_start.y, 0xFFFFFFFF);
		player->angle -= 1;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(player->mlx);
	thickenize_pixel(player, player->p_start.x, player->p_start.y, 0x00FF0000);
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
	player->p_start.x = WIDTH / 2;
	player->p_start.y = HEIGHT / 2;
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
	//draw_stripe(player);
	draw_map(img, player->map);
	mlx_loop_hook(mlx, &my_loop_hook, player);
    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}

