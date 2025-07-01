#include "so_long.h"

// Draws player move to the next tile (and draws the floor on previous tile)
void	move_player(t_data *data, int x, int y)
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
		{
			data->collectable--;
			draw_tile(data, 0, new_posx, new_posy);
		}
		else if (data->map[new_posy][new_posx] == 'E' && !data->collectable)
			close_window(data, 1);
		draw_tile(data, 0, data->playerx, data->playery);
		data->map[data->playery][data->playerx] = '0';
		data->playery = new_posy;
		data->playerx = new_posx;
		data->map[data->playery][data->playerx] = 'P';
		draw_tile(data, 2, data->playerx, data->playery);
		ft_printf("Current step is [\033[1;33m%d\033[0;37m]\n", ++data->moves);
	}
}

// Keys input action
static int	key_press(int key, t_data *data)
{
	if (!data->moveready)
		return (0);
	if (key == ESC)
		close_window(data, 1);
	else if (key == UP || key == W)
		move_player(data, 0, -1);
	else if (key == LEFT || key == A)
		move_player(data, -1, 0);
	else if (key == DOWN || key == S)
		move_player(data, 0, 1);
	else if (key == RIGHT || key == D)
		move_player(data, 1, 0);
	data->moveready = 0;
	return (0);
}

// Movement delay function when Key is held down
int	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->moveready)
	{
		data->movedelay++;
		if (data->movedelay >= 1000)
		{
			data->moveready = 1;
			data->movedelay = 0;
		}
	}
	return (0);
}

// Main Hooks play
void	hooks_config(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
}
