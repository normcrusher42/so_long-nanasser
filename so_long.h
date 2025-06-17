#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"
# include <stdio.h>
# include "mlx/mlx.h"
# include <stdbool.h>

// Map position //
typedef struct s_map
{
	int	x;
	int	y;
}	t_map;

# ifdef __APPLE__
#  define ESC         53
#  define UP          126
#  define DOWN        125
#  define RIGHT       124
#  define LEFT        123
#  define ON_MOUSE_DW 4
# else
#  define ESC         65307
#  define MOUSE_UP    4
#  define MOUSE_DOWN  5
#  define UP          65362
#  define DOWN        65364
#  define RIGHT       65363
#  define LEFT        65361
#  define ON_MOUSE_DW 4
# endif

typedef struct s_size
{
	int			playerx;
	int			playery;
	int			floorx;
	int			floory;
	int			wallx;
	int			wally;
	int			collectablex;
	int			collectabley;
	int			exitx;
	int			exity;
}	t_size;

//-----------------------//
//      MLX tools        //
//-----------------------//
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*textures[5];
	int			img_width;
	int			img_height;
	int			img_width2;
	int			img_height2;
	int			mapx;
	int			mapy;
	char		**map;
}	t_data;

// Error Handlers //
void		error_out(char error_sign, char **map, char *line, int fd);
void		free_map(char **map, char *line, int fd);

//-----------------------//
//   Map Parsing tools   //
//-----------------------//
char		**map_reader(char *file_path);
char		**dup_map(char **map);
void		tile_size(t_data *data);
void		get_map_size(t_data *data);

// Map Validator //
int			filetype_check(char *file);
void		validate_map(char **map);
void		find_player(char **map, t_map *coords);
void		flood_fill(char **map, t_map coords);
bool		goals_reachable(char **map_cpy);
void		only_player(char **map);


#endif