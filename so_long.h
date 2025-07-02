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
#  define SPACE			49

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
#  define ON_MOUSE_DW	4
#  define SPACE			65

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
	void		*textures[5]; // map tile textures
	void		*frames[12]; // character animation textures
	int			img_width; // floor tile width size
	int			img_height; // floor tile height size
	int			mapx; // map width size
	int			mapy; // map height size
	int			playerx; // player posx
	int			playery; // player posy
	int			collectable; // num of collectables (-- when collected till 0)
	int			moves; // number of steps taken
	int			movedelay; // movement input delay for hold
	int			moveready; // player movement state (1 for movable 0 otherwise)
	int			exitx; // exit posx
	int			exity; // exit posy
	char		**map;
	// all these here are bonus related
	int			smooth_x; // mid-pixel posx
	int			smooth_y; // mid-pixel posy
	int			target_x; // next tile posx
	int			target_y; // next tile posy
	int			moving; // player movement state (1 for movable, 0 otherwise)
	int			last_playerx; // previous tile posx
	int			last_playery; // previous tile posy
	int			collected_pending; // Flag to del collectable after animation
	int			step_log; // flag to track when step is complete
	int			move_speed; // num of pixels sprite will skip
	int			direction; // 0 = down, 1 = left, 2 = right, 3 = up
	int			anim_frame; // curr animation frame
	int			anim_tick; // speed of the animation
	int			buffered_key; // the key that was pressed earlier
	int			key_buffered; // 0 or 1 flag to initiate key buffer
	int			sprinting;
}	t_data;

// Error Handlers //
void		error_out(char error_sign, char **map, char *line, int fd);
void		free_map(char **map, char *line, int fd);
int			close_window(t_data *data, int tick);
void		clean_sprites(t_data *data);

//-----------------------//
//   Map Parsing tools   //
//-----------------------//
char		**map_reader(char *file_path, t_data *data);
char		**dup_map(char **map);
// Map size grabber //
void		tile_size(t_data *data);
void		get_map_size(t_data *data);
// Map Validator //
int			filetype_check(char *file);
void		validate_map(char **map, t_data *data);
void		find_player(char **map, t_data *data);
void		find_exit(char **map, t_data *data);
void		flood_fill(char **map, int x, int y, char c);
bool		goals_reachable(char **map_cpy, char c);
void		only_player(char **map);

//----------------------//
//    Hooks settings    //
//----------------------//
void		hooks_config(t_data *data);
// Game functionality //
int			game_loop(void *param);
int			get_tile_index(char c);

//----------------------//
//     Window Canvas    //
//----------------------//
void		ready_window_render(t_data *data);
void		draw_tile(t_data *data, int tile, int x, int y);
void		move_player(t_data *data, int x, int y);
void		draw_map(t_data *data);

#endif