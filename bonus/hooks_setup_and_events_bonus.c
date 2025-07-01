#include "so_long_bonus.h"

// returns tile defintion to draw
static int	get_tile_index_no_p(char c)
{
	if (c == '1')
		return (1);
	else if (c == 'C')
		return (3);
	else if (c == 'E')
		return (4);
	return (0);
}

static void	redraw_player(t_data *data)
{
	int		i;
	int		px;
	int		py;
	char	current;

	px = data->playerx;
	py = data->playery;
	draw_tile(data, 0, px, py);
	current = data->map[py][px];
	i = get_tile_index_no_p(current);
	if (i)
		draw_tile(data, i, px, py);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->frames[data->direction * 3 + data->anim_frame], data->smooth_x,
		data->smooth_y);
}

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
static void	move_player_dir(t_data *data, int x, int y, int dir)
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
			data->map[new_posy][new_posx] = '0';
			data->collected_pending = 1;
		}
		else if (data->map[new_posy][new_posx] == 'E' && !data->collectable)
			close_window(data, 1);
		update_var(data, new_posx, new_posy);
		data->direction = dir;
	}
}

// Keys input action
static int	key_press(int key, t_data *data)
{
	if (data->moving)
		return (0);
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

void	check_var(t_data *data)
{
	if (data->smooth_x < data->target_x)
			data->smooth_x += data->move_speed;
		else if (data->smooth_x > data->target_x)
			data->smooth_x -= data->move_speed;
		if (data->smooth_y < data->target_y)
			data->smooth_y += data->move_speed;
		else if (data->smooth_y > data->target_y)
			data->smooth_y -= data->move_speed;
		if (data->smooth_x == data->target_x
			&& data->smooth_y == data->target_y)
			{
				data->moving = 0;
				if (data->collected_pending)
				{
					data->collected_pending = 0;
					draw_tile(data, 0, data->playerx, data->playery);
				}
				if (!data->step_log)
				{
					data->step_log = 1;
					ft_printf("Current step is [\033[1;33m%d\033[0;37m]\n", ++data->moves);
				}
			}
}

// Movement delay function when Key is held down
int	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->moving)
	{
		if (++data->anim_tick >= 6)
		{
			data->anim_tick = 0;
			data->anim_frame = (data->anim_frame + 1) % 3;
		}
		check_var(data);
		redraw_player(data);
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
