#include "so_long_bonus.h"

// Keys input action
int	key_press(int key, t_data *data)
{
	if (data->moving)
	{
		data->last_key = key;
		return (0);
	}
	if (key == ESC)
		close_window(data, 1);
	else if (key == UP || key == W)
		move_player_dir(data, 0, -1, 3);
	else if (key == LEFT || key == A)
		move_player_dir(data, -1, 0, 1);
	else if (key == DOWN || key == S)
		move_player_dir(data, 0, 1, 0);
	else if (key == RIGHT || key == D)
		move_player_dir(data, 1, 0, 2);
	return (0);
}

// Ensures it follows up the movement with the last key (for seamless movement)
void	check_last_key(t_data *data)
{
	if (data->smooth_x == data->target_x && data->smooth_y == data->target_y)
	{
		if (data->last_key == UP || data->last_key == W)
			move_player_dir(data, 0, -1, 3);
		else if (data->last_key == LEFT || data->last_key == A)
			move_player_dir(data, -1, 0, 1);
		else if (data->last_key == DOWN || data->last_key == S)
			move_player_dir(data, 0, 1, 0);
		else if (data->last_key == RIGHT || data->last_key == D)
			move_player_dir(data, 1, 0, 2);
		data->last_key = 0;
	}
}
