
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
#define WHITESPACES_LESS "\t\r\f\v"
​
typedef enum e_type
{
	WALKABLE,
	OPEN_DOOR,
	CLOSED_DOOR,
	WALL,
	
} t_type;
​
typedef enum e_error
{
	ERROR_NORTH,
	ERROR_WEST,
	ERROR_SOUTH,
	ERROR_EAST,
	ERROR_FLOOR,
	ERROR_CEILING,
	ERROR_NO,
	ERROR_INVALID,
	
} t_error;
​
typedef enum e_error_color
{
	ERROR_COMMA_CEILING,
	ERROR_COMMA_FLOOR,
	ERROR_NUMBER_CEILING,
	ERROR_NUMBER_FLOOR,
	ERROR_ALPHA_FLOOR,
	ERROR_ALPHA_CEILING,
	ERROR_SPACES_FLOOR,
	ERROR_SPACES_CEILING,
	NO_ERROR,
} t_error_color;

//draw

# define WIDTH 900	
# define HEIGHT 600
# define GRID_WIDTH 6
# define GRID_HEIGHT 6
# define PLAYER_SPEED 0.11
# define ROTATION_SPEED 3
# define MOUSE_SENSITIVITY 5
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
	double		distance;
	double		proj_wall_height;
	int			wall_start;
	int			wall_end;
	int			wall_side;
} t_ray;

typedef struct s_player
{
	double			angle;
	t_fvector		p_start;
	double			fov;
	int				map[GRID_WIDTH][GRID_HEIGHT];
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_west;
	mlx_texture_t	*tex_east;
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
	double 	x;
	double	y;
} 	t_coord;

//linked_list_to_array
char	**transfer_map_to_array(t_map_list *map);

//color_utils
int	check_for_commas(char *str);
int	number_counter(char *str);
int	check_for_alpha(char *str);


//color
uint32_t	rgb_to_uint(int red, int green, int blue);
void	check_numbers(int red, int green, int blue);
void	get_color_floor(t_var *var);
void	get_color_ceiling(t_var *var);
void check_colors(t_var *var);

//textures
char *trim_spaces_string(char *str);
void trim_spaces_textures(t_tex_list *tex);
char *get_string_path(char *str);

//get_textures_and_map
void	get_textures_and_map(char **argv, t_map_list *map, t_tex_list *tex,
			t_var *var);

// get_textures_and_map_utils
int	is_wall_or_field(char type);
void	check_for_empty_line(char *line, t_map_list *map);
int	is_begin_of_map(char *line);

//check_map
int	ft_whitespaces(char c);
int ft_charcmp(char c, char *str);
void check_around_zero(char **map, int line, int character, t_var *var);
void	check_map(char **map, t_var *var);

//init
void	init_variables(t_var *var, t_map_list *map, t_tex_list *tex);

//parser
void	parser(char **argv, t_var *var, t_map_list *map, t_tex_list *tex);
void 	check_numbers(int red, int green, int blue);

//print_errors
void	print_wrong_textures(t_tex_list *tex, t_var *var, t_error error);
void	print_wrong_color(t_error_color error);
void	print_error(char *message);

//parser_linked_list_utils
void	ft_lstadd_back_tex(t_tex_list **lst, t_tex_list *new);
void	ft_lstadd_back_map(t_map_list **lst, t_map_list *new);

//parser_linked_list
void	create_linked_list_for_textures(t_tex_list **tex);
void	create_linked_list_for_map(t_map_list **map);
void	add_node_to_map(char *line, t_map_list **map);
void	add_node_to_tex(char *line, t_tex_list **tex);


// utils
int		check_input(int argc, char **argv);
char	*sl_strjoin(char *s1, char *s2);
int		ft_strcmp(char *first, char *second);


//free_stuff
void free_list_textures(t_tex_list **tex);
void free_var(t_var *var);
void free_list_map(t_map_list **map);
void free_numbers(char **numbers);

//draw
int32_t		draw_it(void);
void		draw_pixel(mlx_image_t *img, int x, int y, uint32_t color);
void		draw_map(mlx_image_t *img, int map[][6]);
void		draw_square(mlx_image_t *img, int x, int y, uint32_t color);
void		draw_fov(t_player *player);


//draw_utils
int			grid_to_pixel(double grid_coordinate, int grid_size, int pixel_size);
double		pixel_to_grid(int pixel_coordinate, int tile_size);
t_fvector	angle_to_vector(double angle);

//movement
void		my_loop_hook(void *param);

//textures
mlx_texture_t	*get_tex(t_ray *ray, t_player *player);
uint32_t		get_wall_color(t_player *player, t_ray *ray);
void			paint_background(t_player *player, t_ray *ray, int x);
void			paint_texture(t_player *player, t_ray *ray, int x);
int				get_x_pos(t_player *player, t_ray *ray, mlx_texture_t *tex);

#endif