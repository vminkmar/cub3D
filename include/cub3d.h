
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
#define WHITESPACES_WITHOUT_SPACES "\t\r\f\v\n"

typedef enum e_type
{
	WALKABLE,
	WALL,
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
	
} t_error;

typedef enum e_error_color
{
	ERROR_COMMA_CEILING,
	ERROR_COMMA_FLOOR,
	ERROR_NUMBER_CEILING,
	ERROR_NUMBER_FLOOR,
	ERROR_ALPHA_FLOOR,
	ERROR_ALPHA_CEILING,
	NO_ERROR,
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


typedef struct s_map
{
	int		height;
	int		width;
	char	**map;
	
}	t_map;

typedef struct s_var
{
	t_map			map;
	mlx_texture_t	*textures[6];
	char			*path_north;
	char			*path_south;
	char			*path_east;
	char			*path_west;
	char			*ceiling_color;
	char			*floor_color;
	uint32_t		color_floor;
	uint32_t		color_ceiling;
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
int32_t	draw_it(void);

#endif