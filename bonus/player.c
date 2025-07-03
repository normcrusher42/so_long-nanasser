#include "so_long_bonus.h"

// Returns tile defintion to draw
int	get_tile_index_bonus(char c)
{
	if (c == '1')
		return (1);
	else if (c == 'C')
		return (3);
	else if (c == 'E')
		return (4);
	else if (c == 'O')
		return (5);
	return (0);
}

// Redraws the player in their current position
void	redraw_player(t_data *data)
{
	int		i;
	int		px;
	int		py;
	char	current;

	px = data->playerx;
	py = data->playery;
	draw_tile(data, 0, px, py);
	current = data->map[py][px];
	i = get_tile_index_bonus(current);
	if (i)
		draw_tile(data, i, px, py);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->frames[data->direction * 3 + data->anim_frame], data->smooth_x,
		data->smooth_y);
}

// Updates & declares necessary variables for next set of operations
static void	update_var(t_data *data, int nx, int ny)
{
	data->last_playerx = data->playerx;
	data->last_playery = data->playery;
	data->playerx = nx;
	data->playery = ny;
	data->target_x = nx * data->img_width;
	data->target_y = ny * data->img_height;
	data->anim_frame = 0;
	data->anim_tick = 1;
	data->moving = 1;
	data->step_log = 0;
}

// Draws player move to the next tile (and draws the floor on previous tile)
void	move_player_dir(t_data *data, int x, int y, int dir)
{
	int	new_posx;
	int	new_posy;

	new_posx = data->playerx + x;
	new_posy = data->playery + y;
	if (data->map[new_posy][new_posx] != '1')
	{
		if (data->map[new_posy][new_posx] == 'E' && data->collectable)
			return ;
		else if (data->map[new_posy][new_posx] == 'C')
			data->collected_pending = 1;
		else if (data->map[new_posy][new_posx] == 'O')
			data->death_pending = 1;
		else if (data->map[new_posy][new_posx] == 'E' && !data->collectable)
			close_window(data, 1);
		update_var(data, new_posx, new_posy);
		data->direction = dir;
	}
	else
	{
		draw_tile(data, 0, data->playerx, data->playery);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->frames[dir * 3 + 0], data->playerx * data->img_width,
			data->playery * data->img_height);
	}
}
