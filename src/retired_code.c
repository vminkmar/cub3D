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

uint32_t get_wall_color(t_player *player, t_ray *ray)
{
	uint32_t wall_color;

	wall_color = WALL;
	if (get_orientation(ray, player) == NORTH)
		wall_color = 0x8CB7DA;
	else if (get_orientation(ray, player) == SOUTH)
		wall_color = 0x00FF00FF;
	else if (get_orientation(ray, player) == WEST)
		wall_color = 0x0000FFFF;
	else if (get_orientation(ray, player) == EAST)
		wall_color = 0xF5F327CC;
	return (wall_color);
}