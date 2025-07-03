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
	if (data->collected_pending)
	{
		data->collected_pending = 0;
		data->collectable--;
		data->map[data->playery][data->playerx] = '0';
		draw_tile(data, 0, data->playerx, data->playery);
	}
	if (data->death_pending)
	{
		data->map[data->playery][data->playerx] = '0';
		draw_tile(data, 0, data->playerx, data->playery);
		ft_printf("\033[1;31mPenelope, why?\n");
		ft_printf("You know I'm too shy and terrified\033[0m\n");
		free_map(data->map, NULL, -1);
		close_window(data, 0);
		exit(0);
	}
}

// Checks Clamping and input buffer status
void	check_var(t_data *data)
{
	int		dx;
	int		dy;

	if (data->smooth_x < data->target_x)
		data->smooth_x += data->move_speed;
	else if (data->smooth_x > data->target_x)
		data->smooth_x -= data->move_speed;
	if (data->smooth_y < data->target_y)
		data->smooth_y += data->move_speed;
	else if (data->smooth_y > data->target_y)
		data->smooth_y -= data->move_speed;
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
	}
}
