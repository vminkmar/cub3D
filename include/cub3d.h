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
# define WIDTH 900	
# define HEIGHT 600
# define MAX_WIDTH 5120
# define MAX_HEIGHT 2880
# define BPP sizeof(int32_t)
# define PLAYER_SPEED 0.11
# define FIELD_OF_VIEW 60
# define ROTATION_SPEED 3
# define MOUSE_SENSITIVITY 5
# define EPSILON 1e-6
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif
# define WHITESPACES " \t\r\f\v\n"
# define WHITESPACES_LESS "\t\r\f\v"

typedef enum e_type
{
	NOTHING,
	OTHERS,
	WALKABLE,
	WALL,
	OPEN_DOOR,
	CLOSED_DOOR,
	
} t_type;

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
	ERROR_INVALID_DOOR,
	ERROR_NORTH_MULTIPLE,
	ERROR_WEST_MULTIPLE,
	ERROR_SOUTH_MULTIPLE,
	ERROR_EAST_MULTIPLE,
	ERROR_FLOOR_MULTIPLE,
	ERROR_CEILING_MULTIPLE,
	
} t_error;

typedef enum e_error_syntax
{
	ERROR_UPPER,
	ERROR_SPACES,
	ERROR_SYNTAX,
	ERROR_SYNTAX_NORTH,
	ERROR_SYNTAX_EAST,
	ERROR_SYNTAX_SOUTH,
	ERROR_SYNTAX_WEST,
	NO_ERROR_SYNTAX,
	NO_ERROR,

} t_error_syntax;

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
	ERROR_WHITESPACES_FLOOR,
	ERROR_WHITESPACES_CEILING,
	NO_COLOR_ERROR,
} t_error_color;


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

typedef enum e_wall_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
} t_wall_orientation;

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
	int				counter_p_start;
	double			angle;
	t_fvector		p_start;
	double			fov;
} 	t_player;

typedef struct s_map
{
	int				max_height;
	int				max_width;
	char			**map;
	char			*path_north;
	char			*path_south;
	char			*path_east;
	char			*path_west;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_west;
	mlx_texture_t	*tex_east;
	mlx_texture_t	*tex_door;
	char			*floor_color;
	char			*ceiling_color;
	uint32_t		color_floor;
	uint32_t		color_ceiling;
	int				path_east_counter;
	int				path_south_counter;
	int				path_west_counter;
	int				path_north_counter;
	int				floor_color_counter;
	int				ceiling_color_counter;
}	t_map;

//draw
typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	t_player		*player;
}	t_data;

//linked_list_to_array
char			**transfer_map_to_array(t_map_list *map, t_data *data);
void			get_max_with(char *str, t_data *data);

// syntax_check
void syntax_textures(t_tex_list *tex);



//edit_textures
void	trim_before_and_after(t_tex_list *tex);


//color_utils
int				check_for_commas(char *str);
int				number_counter(char **str);
int				check_for_alpha(char **str);
void			check_for_spaces(char *str, int flag);	

//color
int				rgb_to_uint(int red, int green, int blue, int alpha);
void			check_numbers(int red, int green, int blue);
void			get_color_floor(t_data *data);
void			get_color_ceiling(t_data *data);
void			check_colors(t_data *data, int i, int issue, char **colors);

//textures
char			*trim_spaces_string(char *str);
void			trim_spaces_textures(t_tex_list *tex);
char			*get_string_path(char *str);

//get_textures_and_map
void			get_textures_and_map(char **argv, t_map_list *map,
					t_tex_list *tex,
					t_data *data);

// get_textures_and_map_utils
int				is_wall_or_field(char type);
void			check_for_empty_line(char *line, t_map_list *map);
int				is_begin_of_map(char *line);

//check_map
int				ft_whitespaces(char c);
int				ft_charcmp(char c, char *str);
void			check_around_zero(char **map, int line, int character, t_data *data);
void			check_map(char **map, t_data *data);

//init
void			init_variables(t_data *data, t_map_list *map, t_tex_list *tex);

//parser
void			parser(char **argv, t_data *data);
void 			check_numbers(int red, int green, int blue);

//print_errors
void			print_wrong_textures(t_tex_list *tex, t_data *data, t_error error);
void			print_wrong_color(t_error_color error);
void			print_multiple_textures(t_tex_list *tex, t_data *data, t_error error);
void			print_error(char *message);

//parser_linked_list_utils
void			ft_lstadd_back_tex(t_tex_list **lst, t_tex_list *new);
void			ft_lstadd_back_map(t_map_list **lst, t_map_list *new);

//parser_linked_list
void			create_linked_list_for_textures(t_tex_list **tex);
void			create_linked_list_for_map(t_map_list **map);
void			add_node_to_map(char *line, t_map_list **map);
void			add_node_to_tex(char *line, t_tex_list **tex);

// utils
int				check_input(int argc, char **argv);
char			*sl_strjoin(char *s1, char *s2);
int				ft_strcmp(char *first, char *second);

//free_stuff
void			free_list_textures(t_tex_list **tex);
void			free_data(t_data *data);
void			free_list_map(t_map_list **map);
void			free_numbers(char **numbers);

//main
void			init_data(t_data *data);
void			init_player(t_data *data);

//raycast
void			raycaster(t_data *data);
void			draw_fov(t_player *player, t_data *data);
void			cast_ray(t_player *player, t_data *data, double angle, int x);
void			init_ray(t_player *player, t_ray *ray, double angle);
void			get_stepsize(t_ray *ray);

//raycast2
void			get_steps(t_ray *ray);
void			set_wall(t_ray *ray, t_player *player, double angle);
double			distance_to_plane(double distance, double angle,
					double player_angle);
void			wall_hit(t_data *data, t_ray *ray, int *hit);

//draw
void			paint_background(t_data *data, t_ray *ray, int x);
void			paint_texture(t_data *data, t_ray *ray, int x);
int				get_x_pos(t_player *player, t_ray *ray, mlx_texture_t *tex);
mlx_texture_t	*get_tex(t_data *data, t_ray *ray);

//draw_utils
int				grid_to_pixel(double grid_coordinate, int grid_size,
					int pixel_size);
double			pixel_to_grid(int pixel_coordinate, int tile_size);
t_fvector		angle_to_vector(double angle);
void			draw_pixel(mlx_image_t *img, int x, int y, uint32_t color);

//movement
void			my_loop_hook(void *param);
void			check_mouse_pos(t_data *data);
void			move_player(t_data *data, keys_t key);


//directions
int				wall_collision(char **map, double x, double y);
void			move_down(t_data *data, double tmp_x, double tmp_y);
void			move_up(t_data *data, double tmp_x, double tmp_y);
void			move_left(t_data *data, double tmp_x, double tmp_y);
void			move_right(t_data *data, double tmp_x, double tmp_y);

//doors
void			cast_door_ray(t_data *data, t_player *player);
void			open_close_door(t_data *data, t_ray *ray, int map_x, int map_y);
void			interac_hook(mlx_key_data_t keydata, void *param);

//textures
mlx_texture_t	*get_tex(t_data *data, t_ray *ray);
uint32_t		get_wall_color(t_player *player, t_ray *ray);
void			paint_background(t_data *data, t_ray *ray, int x);
void			paint_texture(t_data *data, t_ray *ray, int x);
int				get_x_pos(t_player *player, t_ray *ray, mlx_texture_t *tex);

#endif