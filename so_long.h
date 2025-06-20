#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"
# include <stdio.h>
# include "mlx/mlx.h"
# include <stdbool.h>

// Keybinds Definers //
# ifdef __APPLE__
#  define ESC			53
#  define UP			126
#  define DOWN			125
#  define RIGHT			124
#  define LEFT			123
#  define W				13
#  define A				0
#  define S				1
#  define D				2
#  define ON_MOUSE_DW	4
# else
#  define ESC			65307
#  define MOUSE_UP		4
#  define MOUSE_DOWN	5
#  define UP			65362
#  define DOWN			65364
#  define RIGHT			65363
#  define LEFT			65361
#  define W				119
#  define A				97
#  define S				115
#  define D				100
#  define ON_MOUSE_DW 4
# endif

//------------------------//
//   Sprite image sizes   //
//------------------------//
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

//------------------------//
//   Map & Texture data   //
//------------------------//
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*textures[5];
	int			img_width;
	int			img_height;
	int			mapx;
	int			mapy;
	int			playerx;
	int			playery;
	int			collectable;
	int			moves;
	int			movedelay;
	int			moveready;
	char		**map;
}	t_data;

// Error Handlers //
void		error_out(char error_sign, char **map, char *line, int fd);
void		free_map(char **map, char *line, int fd);
int			close_window(t_data *data, int tick);

void		tile_size(t_data *data);
void		get_map_size(t_data *data);

//-----------------------//
//   Map Parsing tools   //
//-----------------------//
char		**map_reader(char *file_path, t_data *data);
char		**dup_map(char **map);
// Map Validator //
int			filetype_check(char *file);
void		validate_map(char **map, t_data *data);
void		find_player(char **map, t_data *data);
void		flood_fill(char **map, int x, int y);
bool		goals_reachable(char **map_cpy);
void		only_player(char **map);

#endif