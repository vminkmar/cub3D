#include "../../include/cub3d.h"

void draw_square(t_data *data, int x, int y, uint32_t color)
{
	int new_x = x;
	int new_y = y;
	int count_x;
	int count_y;

	count_y = 0;
	while(count_y < HEIGHT / data->map->max_height)
	{
		new_x = x;
		count_x = 0;
		while(count_x < WIDTH / data->map->max_width)
		{
			mlx_put_pixel(data->minimap_img, new_x, new_y, color);
			new_x++;
			count_x++;
		}
		new_y++;
		count_y++;
	}
}

/* void draw_minimap(t_data *data, char **map)
{
	int x = 0;
	int y = 0;
	int	i;
	int	j;
	int minimap_width;
	int minimap_height;

	j = 0;
	i = 0;
	(void) map;
	minimap_width = WIDTH / 4;
	minimap_height = HEIGHT / 4;
	while(i < minimap_height)
	{
		j = 0;
		x = 0;
		while(j < minimap_width)
		{
			draw_pixel(data->minimap_img, x, y, 0x000000FF);
			j++;
			x++;
		}
		y++;
		i++;
	}

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	int minimap_dims = data->map->max_width / minimap_width;
	int start;
	while(i < data->map->max_height)
	{
		j = 0;
		x = 0;
		while(j < data->map->max_width)
		{
			start = 0;
			while(start < minimap_dims)
			{
				if(map[i][j] ==  WALL)
					draw_pixel(data->minimap_img, x, y, 0x000000FF);
				else
					draw_pixel(data->minimap_img, x, y, 0xFFFFFFFF);
				x++;
				start++;
			}
			j++;
		}
		i++;
	}
} */

void	draw_minimap_square(t_data *data, int j, int i, int x, int y)
{
	int			end_x;
	int			end_y;
	int			row;
	int			col;
	uint32_t	color;

	row = y;
	end_x = x + data->map->minimap_dims;
	end_y = y + data->map->minimap_dims;
	if (data->map->map[i][j] == WALKABLE)
		color = 0xFFFFFFFF;
	if (data->map->map[i][j] == WALL)
		color = 0x000000FF;
	if (data->map->map[i][j] == OPEN_DOOR)
		color = 0x0000FFFF;
	while (row < end_y)
	{
		col = x;
		while (col < end_x)
		{
			draw_pixel(data->minimap_img, col, row, color);
			col++;
		}
		row++;
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	y = 0;
	data->map->minimap_dims = (WIDTH / 4) / data->map->max_width;
	i = 0;
	while (i < data->map->max_height)
	{
		x = 0;
		j = 0;
		while (j < data->map->max_width)
		{
			draw_minimap_square(data, j, i, x, y);
			x += data->map->minimap_dims;
			j++;
		}
		y += data->map->minimap_dims;
		i++;
	}
}
