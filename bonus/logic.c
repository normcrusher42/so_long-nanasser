#include "so_long_bonus.h"

// abs recreation meant to clamp sprite properly in smooth_x/y
static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

// Checks the info of the destination step
static void	check_step(t_data *data)
{
	char	tile;
	int		tile_index;

	if (data->collected_pending)
	{
		data->collected_pending = 0;
		data->collectable--;
		data->map[data->playery][data->playerx] = '0';
		draw_tile(data, 0, data->playerx, data->playery);
	}
	else
	{
		tile = data->map[data->playery][data->playerx];
		tile_index = get_tile_index_no_p(tile);
		draw_tile(data, 0, data->playerx, data->playery);
		if (tile_index)
			draw_tile(data, tile_index, data->playerx, data->playery);
	}
	if (!data->step_log)
	{
		data->step_log = 1;
		display_status(data);
	}
}

// Checks Clamping and input buffer status
void	check_var(t_data *data)
{
	int		dx;
	int		dy;
	int		index;
	char	tile;

	dx = data->target_x - data->smooth_x;
	dy = data->target_y - data->smooth_y;
	if (ft_abs(dx) <= data->move_speed && ft_abs(dy) <= data->move_speed)
	{
		data->moving = 0;
		data->smooth_x = data->target_x;
		data->smooth_y = data->target_y;
		check_step(data);
		if (data->key_buffered)
		{
			data->key_buffered = 0;
			draw_tile(data, 0, data->last_playerx, data->last_playery);
			tile = data->map[data->last_playery][data->last_playerx];
			index = get_tile_index_no_p(tile);
			if (index)
				draw_tile(data, index, data->last_playerx, data->last_playery);
			key_press(data->buffered_key, data);
		}
	}
}
