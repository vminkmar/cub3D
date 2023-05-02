
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

typedef enum e_error
{
	ERROR_NORTH,
	ERROR_WEST,
	ERROR_SOUTH,
	ERROR_EAST,
	ERROR_FLOOR,
	ERROR_CEILING,
	ERROR_NO,
	
} t_error;

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
	t_map			map;
	mlx_texture_t	*textures[6];
	char			*path_north;
	char			*path_south;
	char			*path_east;
	char			*path_west;
	char			*floor_color;
	char			*ceiling_color;
}	t_var;

//draw

# define WIDTH 500
# define HEIGHT 500

typedef struct s_player
{
	double 	x;
	double	y;
	mlx_image_t *img;
	mlx_t *mlx;
} 	t_player;

typedef struct s_coord
{
	double 	x;
	double	y;
} 	t_coord;


//parser
void parser(char **argv, t_var *var, t_map_list *map, t_tex_list *tex);
void print_wrong_texures(t_tex_list *tex, int flag);


//parser_utils
void create_linked_list_for_textures(t_tex_list **tex);
void create_linked_list_for_map(t_map_list **map);
int ft_strcmp(char *first, char *second);


// utils
int check_input(int argc, char **argv);
char	*sl_strjoin(char *s1, char *s2);

//error_management
void print_error(char *message);


//free_stuff
void free_textures(t_tex_list **tex);
void free_var(t_var *var);

//draw
int32_t	draw_it(void);

#endif