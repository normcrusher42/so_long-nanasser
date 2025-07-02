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
			data->collected_pending = 1;
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

void	is_sprinting(t_data *data)
{
	ft_printf("over here\n");
	if (data->sprinting == 0)
		data->sprinting = 1;
	else
		data->sprinting = 0;
	if (data->sprinting == 1)
		data->move_speed = 12;
	else
		data->move_speed = 8;
}

// Keys input action
static int	key_press(int key, t_data *data)
{
	if (data->moving)
	{
		data->buffered_key = key;
		data->key_buffered = 1;
		return (0);
	}
	data->key_buffered = 0;
	if (key == SPACE)
		is_sprinting(data);
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

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	display_status(t_data *data)
{
	char	*moves_str = "moves : ";
	char	*num;
	char	*num2;
	char	*collectables = "collectables : ";

	num = ft_itoa(data->moves);
	num2 = ft_itoa(data->collectable);
	moves_str = ft_strjoin(moves_str, num);
	collectables = ft_strjoin(collectables, num2);
	draw_tile(data, 1, 0, 0);
	draw_tile(data, 1, 1, 0);
	draw_tile(data, 1, 2, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 20, 0xFFFF00, moves_str);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 35, 0xFF2E2E, collectables);
	free(moves_str);
	free(collectables);
	free(num);
	free(num2);
	data->moves++;
}

void	check_step(t_data *data)
{
	char	tile;
	int tile_index;

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
}
void	check_var(t_data *data)
{
	int		dx;
	int		dy;

	dx = data->target_x - data->smooth_x;
	dy = data->target_y - data->smooth_y;
	if (ft_abs(dx) <= data->move_speed && ft_abs(dy) <= data->move_speed)
		{
			data->moving = 0;
			data->smooth_x = data->target_x;
			data->smooth_y = data->target_y;
			check_step(data);
			if (!data->step_log)
			{
				data->step_log = 1;
				display_status(data);
			}
			if (data->key_buffered)
			{
				data->key_buffered = 0;
				draw_tile(data, 0, data->last_playerx, data->last_playery);
				char tile = data->map[data->last_playery][data->last_playerx];
				int index = get_tile_index_no_p(tile);
				if (index)
					draw_tile(data, index, data->last_playerx, data->last_playery);
				key_press(data->buffered_key, data);
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
		if (++data->anim_tick >= 700)
		{
			data->anim_tick = 0;
			data->anim_frame = (data->anim_frame + 1) % 3;
			if (data->smooth_x < data->target_x)
				data->smooth_x += data->move_speed;
			else if (data->smooth_x > data->target_x)
				data->smooth_x -= data->move_speed;
			if (data->smooth_y < data->target_y)
				data->smooth_y += data->move_speed;
			else if (data->smooth_y > data->target_y)
				data->smooth_y -= data->move_speed;
			check_var(data);
			draw_tile(data, 0, data->last_playerx, data->last_playery);
			redraw_player(data);
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
