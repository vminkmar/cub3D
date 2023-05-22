#include "../../include/cub3d.h"

void	draw_minimap_square(t_data *data, int j, int i, t_ivector coords)
{
	int			end_x;
	int			end_y;
	int			row;
	int			col;
	uint32_t	color;

	row = coords.y;
	end_x = coords.x + data->map->minimap_dims;
	end_y = coords.y + data->map->minimap_dims;
	if (data->map->map[i][j] == WALKABLE)
		color = (uint32_t)WHITE;
	if (data->map->map[i][j] == WALL || data->map->map[i][j] == OTHERS)
		color = (uint32_t)BLACK;
	if (data->map->map[i][j] == CLOSED_DOOR)
		color = (uint32_t)RED;
	if (i == (int)data->player->p_start.y && j == (int)data->player->p_start.x)
		color = (uint32_t)GREEN;
	while (row < end_y)
	{
		col = coords.x;
		while (col < end_x)
			draw_pixel(data->minimap_img, col++, row, color);
		row++;
	}
}

void	draw_minimap(t_data *data)
{
	t_ivector	coords;
	int			i;
	int			j;

	coords.x = 0;
	coords.y = 0;
	i = 0;
	if (data->map->minimap_dims < 1)
		data->map->minimap_dims = 1;
	while (i < data->map->max_height)
	{
		coords.x = 0;
		j = 0;
		while (j < data->map->max_width - 1)
		{
			draw_minimap_square(data, j, i, coords);
			coords.x += data->map->minimap_dims;
			j++;
		}
		coords.y += data->map->minimap_dims;
		i++;
	}
	printf("%i\n", (int)data->player->p_start.x);
	printf("%i\n", (int)data->player->p_start.y);
	printf("%i\n", data->map->minimap_dims);
	int x = (int)data->player->p_start.x / WIDTH * (data->map->minimap_dims * data->map->max_width);
	int y = (int)data->player->p_start.y / HEIGHT * (data->map->minimap_dims * data->map->max_height);
	draw_pixel(data->minimap_img, x, y, 0xFFFFFF);
}
