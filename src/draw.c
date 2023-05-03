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

void	draw_line(mlx_image_t *img, double x, double y, uint32_t color)
{
	double	dx;
	double	dy;
	double	pix_x;
	double	pix_y;
	int		put_pix;

	dx = 0;
	dy = y + 10 - y;
	put_pix = sqrt((dx * dx) + (dy * dy));
	dx /= put_pix;
	dy /= put_pix;
	pix_x = x;
	pix_y = y;
	while (put_pix)
	{
		mlx_put_pixel(img, x, y, color);
		pix_x = pix_x + dx;
		pix_y = pix_y + dy;
		put_pix--;
	}
}

void thickenize_pixel(mlx_image_t *img, double x, double y, uint32_t color)
{
    double i, j;

    i = -3;
    while (i <= 3)
    {
        j = -3;
        while (j <= 3)
        {
            if (i == 0 && j == 0)
                mlx_put_pixel(img, x + i, y + j, color);
            else
                mlx_put_pixel(img, x + i, y + j, color);
            j++;
        }
        i++;
    }
	draw_line(img, x, y, 0xFF0000FF);
}

void my_loop_hook(void *param)
{
	t_player *player;
	
	player = (t_player *)param;
	if(mlx_is_key_down(player->mlx, MLX_KEY_RIGHT))
	{
		thickenize_pixel(player->img, player->x, player->y, 0xFFFFFFFF);
		player->x += 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_LEFT))
	{
		thickenize_pixel(player->img, player->x, player->y, 0xFFFFFFFF);
		player->x -= 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_DOWN))
	{
		thickenize_pixel(player->img, player->x, player->y, 0xFFFFFFFF);
		player->y += 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_UP))
	{
		thickenize_pixel(player->img, player->x, player->y, 0xFFFFFFFF);
		player->y -= 5;
	}
	if(mlx_is_key_down(player->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(player->mlx);
	thickenize_pixel(player->img, player->x, player->y, 0x00FF0000);
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
				draw_square(img, x, y, 0xFF000000);
			j++;
			x += WIDTH / 4;
		}
		y += HEIGHT / 4;
		i++;
	}
}

int32_t	main(void)
{
	int map[4][4] =
	{ 	{0, 0, 0, 1},
		{1, 1, 0, 1},
		{1, 0, 1, 0},
		{1, 0, 1, 0}
	};
	
	t_player *player;
	
	player = malloc(sizeof(t_player));
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	
	
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
	draw_map(img, map);
	mlx_loop_hook(mlx, &my_loop_hook, player);
    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}

