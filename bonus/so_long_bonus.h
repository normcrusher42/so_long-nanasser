#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../so_long.h"

// ───────────── Rendering / Animation ───────────── //
int		default_tile_theme(t_data *data);
void	sea_tile_theme(t_data *data);
void	redraw_player(t_data *data);
int		get_tile_index_bonus(char c);

// ───────────── Movement ───────────── //
void	move_player_dir(t_data *data, int x, int y, int dir);
void	check_var(t_data *data);
void	check_last_key(t_data *data);

// ───────────── Input ───────────── //
int		key_press(int key, t_data *data);

// ───────────── HUD / Display ───────────── //
void	display_status(t_data *data);

#endif