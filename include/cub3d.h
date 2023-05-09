/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:13:20 by vminkmar          #+#    #+#             */
/*   Updated: 2023/05/09 13:49:36 by mgraefen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "Libft/libft.h"
# include "../include/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <string.h> 
# define MAX_WIDTH 5120
# define MAX_HEIGHT 2880
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif
#define WHITESPACES " \t\r\f\v\n"

enum e_walls
{
	FLOOR,
	WALL,
};

typedef struct s_map_list
{
	char				*content;
	int					empty_line;
	struct s_map_list	*next;
}	t_map_list;

typedef struct s_tex_list
{
	char				*content;
	int					counter;
	struct s_tex_list	*next;
}	t_tex_list;


typedef struct s_map
{
	enum e_walls	walls;
	double			height;
	double			width;

	char			**map;
	
}	t_map;

typedef struct s_var
{
	t_map	map;
	mlx_texture_t	*textures[6];
	char			*path_north;
	char			*path_south;
	char			*path_east;
	char			*path_west;
	char			*floor_color;
	char			*ceiling_color;
}	t_var;

//draw

# define WIDTH 900	
# define HEIGHT 600
# define GRID_WIDTH 6
# define GRID_HEIGHT 6
# define PLAYER_SPEED 0.11
# define ROTATION_SPEED 1.5
# define EPSILON 1e-6

# define CEILING	0xFF0000FF
# define WALL		0x00FF00FF
# define FLOOR		0xFF00FF00

typedef struct s_fvector
{
	double x;
	double y;
}	t_fvector;

typedef struct s_ivector
{
	int x;
	int y;
}	t_ivector;

typedef struct s_ray
{
	t_fvector	start;
    t_fvector	dir;
	t_fvector	step_size;
	t_ivector	map_check;
	t_fvector	length;
	t_ivector	step;
	t_fvector	interception;
} t_ray;

typedef struct s_player
{
	double		angle;
	t_fvector	p_start;
	double		fov;
	int			map[GRID_WIDTH][GRID_HEIGHT];
	mlx_t		*mlx;
	mlx_image_t *img;
} 	t_player;

typedef enum e_wall_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
} t_wall_orientation;


typedef enum e_coords
{
	x_dim,
	y_dim,
} t_coords;


//parser
void		parser(char **argv, t_var *var, t_map_list *map, t_tex_list *tex);
void		print_wrong_texures(t_tex_list *tex, int flag);


//parser_utils
void		create_linked_list_for_textures(t_tex_list **tex);
void		create_linked_list_for_map(t_map_list **map);
int			ft_strcmp(char *first, char *second);


// utils
int			check_input(int argc, char **argv);
char		*sl_strjoin(char *s1, char *s2);

//error_management
void		print_error(char *message);


//free_stuff
void		free_textures(t_tex_list **tex);
void		free_var(t_var *var);

//draw
int32_t		draw_it(void);
void draw_map(mlx_image_t *img, int map[][6]);
void draw_square(mlx_image_t *img, int x, int y, uint32_t color);
void	draw_fov(t_player *player);


//draw_utils
int			grid_to_pixel(double grid_coordinate, int grid_size, int pixel_size);
double		pixel_to_grid(int pixel_coordinate, int tile_size);
t_fvector	angle_to_vector(double angle);

//movement
void		my_loop_hook(void *param);

//textures
uint32_t	get_wall_color(t_ray *ray);



#endif