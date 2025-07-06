#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../so_long.h"

// ───────────── Rendering / Animation ───────────── //
// Theming //
void	map_theme(t_data *data, char *theme);
void	default_tile_theme(t_data *data);
void	sea_tile_theme(t_data *data);
// Player and tile textures //
void	redraw_player(t_data *data);
int		get_tile_index_bonus(char c);
void	draw_tile_obstacle(t_data *data, int tile, int x, int y);
// Background animations //
void	exit_anim_bonus(t_data *data);
void	obstacle_anim(t_data *data);

// ───────────── Movement ───────────── //
void	move_player_dir(t_data *data, int x, int y, int dir);
void	check_var(t_data *data);
void	check_last_key(t_data *data);

// ───────────── Input ───────────── //
int		key_press(int key, t_data *data);

// ───────────── HUD / Display ───────────── //
void	display_status(t_data *data);

// ───────────── Obstacle utils ───────────── // 
void	count_obstacle(t_data *data);
void	save_obstacles(t_data *data);

#endif