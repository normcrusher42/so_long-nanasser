#include "so_long_bonus.h"

// Displays info related to steps taken and collectables left
void	display_status(t_data *data)
{
	char	*moves_str;
	char	*num;
	char	*num2;
	char	*collectables;

	moves_str = "moves : ";
	collectables = "collectables : ";
	num = ft_itoa(data->moves);
	num2 = ft_itoa(data->collectable);
	moves_str = ft_strjoin(moves_str, num);
	collectables = ft_strjoin(collectables, num2);
	draw_tile(data, 1, 0, 0);
	draw_tile(data, 1, 1, 0);
	draw_tile(data, 1, 2, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 20, 0xFFFF00, moves_str);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 35, 0xFF2E2E,
		collectables);
	free(moves_str);
	free(collectables);
	free(num);
	free(num2);
	data->moves++;
}

// Handles events upon reloading hooks again (game speed, tile status, etc..)
int	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->moving)
	{
		if (++data->anim_tick >= 950)
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
	if (data->last_key)
		check_last_key(data);
	return (0);
}

// Main Hooks play
void	hooks_config(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
}
