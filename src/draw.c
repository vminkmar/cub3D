#include "../include/cub3d.h"

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
#define BPP sizeof(int32_t)

void draw_square(mlx_image_t *img, int x, int y, uint32_t color)
{
	int new_x = x;
	int new_y = y;
	int count_x;
	int count_y;

	count_y = 0;
	while(count_y < HEIGHT / GRID_HEIGHT)
	{
		new_x = x;
		count_x = 0;
		while(count_x < WIDTH / GRID_WIDTH)
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

void get_steps(t_ray *ray)
{
    if(ray->dir.x < 0)
    {
        ray->step.x = -1;
        ray->length.x = fabs((ray->start.x - (float)ray->map_check.x) * ray->step_size.x);
    }
    else
    {
        ray->step.x = 1;
        ray->length.x = fabs(((float)ray->map_check.x + 1 - ray->start.x) * ray->step_size.x);
    }
    if(ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->length.y = fabs((ray->start.y - (float)ray->map_check.y) * ray->step_size.y);
    }
    else
    {
        ray->step.y = 1;
        ray->length.y = fabs(((float)ray->map_check.y + 1 - ray->start.y) * ray->step_size.y);
    }
}

void get_stepsize(t_ray *ray)
{
	ray->step_size.x = fabs(1 / ray->dir.x + EPSILON);
    ray->step_size.y = fabs(1 / ray->dir.y + EPSILON);
}

void wall_hit(t_player *player, t_ray *ray, float *distance, int *hit)
{
	if(ray->length.x < ray->length.y)
	{
		ray->wall_side = 0;
		ray->map_check.x += ray->step.x;
		*distance = ray->length.x;
		ray->length.x += ray->step_size.x;
	}
	else
	{
		ray->wall_side = 1;
		ray->map_check.y += ray->step.y;
		*distance = ray->length.y;
		ray->length.y += ray->step_size.y;
	}
	//printf("map_check: (%d, %d)\n", ray->map_check.x, ray->map_check.y);
	if((ray->map_check.x >= 0 && ray->map_check.x < GRID_WIDTH) && (ray->map_check.y >= 0 && ray->map_check.y < GRID_HEIGHT))
	{
		if(player->map[ray->map_check.y][ray->map_check.x] == 1)
			*hit = 1;
	}
}

void draw_line_to_interception(t_player *player, uint32_t color, t_fvector start, t_fvector interception) {
    int start_pixel_x = grid_to_pixel(start.x, GRID_WIDTH, WIDTH);
    int start_pixel_y = grid_to_pixel(start.y, GRID_HEIGHT, HEIGHT);
    int end_pixel_x = grid_to_pixel(interception.x, GRID_WIDTH, WIDTH);
    int end_pixel_y = grid_to_pixel(interception.y, GRID_HEIGHT, HEIGHT);
    
    int dx = abs(end_pixel_x - start_pixel_x);
    int dy = abs(end_pixel_y - start_pixel_y);
    int sx = (start_pixel_x < end_pixel_x) ? 1 : -1;
    int sy = (start_pixel_y < end_pixel_y) ? 1 : -1;
    int err = dx - dy;
    
    while (start_pixel_x != end_pixel_x || start_pixel_y != end_pixel_y) {
        int pixel_x = start_pixel_x;
        int pixel_y = start_pixel_y;
        draw_pixel(player->img, pixel_x, pixel_y, color);
        
        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            start_pixel_x += sx;
        }
        if (err2 < dx) {
            err += dx;
            start_pixel_y += sy;
        }
    }
}

void	draw_one_stripe(t_player *player, double distance, int x, uint32_t wall_color)
{
	int y;
	int wall_start;
	int	wall_end;
	double proj_wall_height;
	uint32_t color;

	y = 0;
	if(distance <= 0.0)
		return ;
	proj_wall_height = ((double)HEIGHT / distance);
    wall_start = (HEIGHT - proj_wall_height) / 2;
    wall_end = wall_start + proj_wall_height;

    while (y < HEIGHT)
    {
        if (y < wall_start)
            color = CEILING;
        else if (y < wall_end)
            color = wall_color;
        else
            color = FLOOR;
		if(x > 0 && x < WIDTH && (y > 0 && y < HEIGHT))
        	mlx_put_pixel(player->img, x, y, color);
		y++;
    }
}

void init_ray(t_player *player, t_ray *ray, double angle)
{
	ray->length.x = 0;
	ray->length.y = 0;
	ray->start.x = player->p_start.x;
	ray->start.y = player->p_start.y;
	ray->map_check.x = (int)ray->start.x;
	ray->map_check.y = (int)ray->start.y;
	ray->dir = angle_to_vector(angle);
}


double distance_to_plane(double distance, double angle, double player_angle)
{
    double diff_angle;
	double perp_distance;

	diff_angle = (angle * (M_PI / 180.0)) - (player_angle * (M_PI / 180.0));
	perp_distance = distance * cos(diff_angle);
    return fabs(perp_distance);
}

void cast_ray(t_player *player, double angle, int x)
{	
	t_ray		*ray;
	int			hit;
	float		distance;
	float		max_distance;
	uint32_t	wall_color;
	
	max_distance = sqrt(GRID_HEIGHT * GRID_HEIGHT) + (GRID_WIDTH * GRID_WIDTH);
	distance = 0;
	hit = 0;
	ray = malloc(sizeof(t_ray));
	init_ray(player, ray, angle);
	get_stepsize(ray);
	get_steps(ray);
	while(!hit && distance + EPSILON < max_distance)
		wall_hit(player, ray, &distance, &hit);
	if(hit)
	{
		ray->interception.x = ray->start.x + ray->dir.x * distance;
		ray->interception.y = ray->start.y + ray->dir.y * distance;
		distance = distance_to_plane(distance, angle, player->angle);
		wall_color = get_wall_color(player, ray);
		draw_one_stripe(player, distance, x, wall_color);
		//draw_line_to_interception(player, color, ray->start, ray->interception);
	}
}

void	draw_fov(t_player *player)
{
	double	current_angle;
	double	end_angle;
	double	step;
	int		x;
	
	current_angle = player->angle - (player->fov / 2);
	end_angle = player->angle + (player->fov / 2);
	step = player->fov / WIDTH;
	x = 0;
	while (current_angle < end_angle)
	{
		cast_ray(player, current_angle, x);
		x++;
		current_angle += step;
	} 
}

void thickenize_pixel(t_player *player, double x, double y, uint32_t color)
{
    double i;
	double j;

	int	px_x;
	int	px_y;
	px_x = grid_to_pixel(x, GRID_WIDTH, WIDTH);
	px_y = grid_to_pixel(y, GRID_HEIGHT, HEIGHT);

    i = -3;
    while (i <= 3)
    {
        j = -3;
        while (j <= 3)
        {
            if (i == 0 && j == 0)
			{
				if (y + j) 
                	draw_pixel(player->img, px_x + i, px_y + j, color);
			}
            else
			{
				if(y + j)
				{
                	draw_pixel(player->img, px_x + i, px_y + j, color);
				}
			}
            j++;
        }
        i++;
    }
	//draw_fov(player);
}

void draw_map(mlx_image_t *img, int map[][6])
{
	int x = 0;
	int y = 0;
	int	i;
	int	j;
	j = 0;
	i = 0;
	while(i < GRID_HEIGHT)
	{
		j = 0;
		x = 0;
		while(j < GRID_WIDTH)
		{
			if(map[i][j])
				draw_square(img, x, y, 0x000000FF);
			else
				draw_square(img, x, y, 0xFFFFFFFF);
			j++;
			x += WIDTH / GRID_WIDTH;
		}
		y += HEIGHT / GRID_HEIGHT;
		i++;
	}
}

int32_t	main(void)
{
	t_player *player;
	
	player = malloc(sizeof(t_player));
	player->p_start.x = GRID_WIDTH / 2;
	player->p_start.y = GRID_HEIGHT / 2;
	player->angle = 90;
	player->fov = 60;
	int map[6][6] =
	{ 	{1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1},
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
	//draw_map(img, player->map);
	mlx_loop_hook(mlx, &my_loop_hook, player);
    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}

