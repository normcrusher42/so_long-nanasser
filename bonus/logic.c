#include "so_long_bonus.h"

// Counts the number of obstacles in the map
void	count_obstacle(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'O')
				data->obstacle_count++;
			j++;
		}
	}
}

// Saves the coordinates of the obstacles in the map
void	save_obstacles(t_data *data)
{
	int	x;
	int	y;
	int	i;

	data->obstacles = malloc(sizeof(t_point) * data->obstacle_count);
	if (!data->obstacles)
		error_out('M', data->map, NULL, -1);
	y = 0;
	i = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'O')
			{
				data->obstacles[i].x = x;
				data->obstacles[i++].y = y;
			}
			x++;
		}
		y++;
	}
}

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
		free_map(data->map, NULL, -1);
		ft_printf("\033[1;31mPenelope, why?\n");
		ft_printf("You know I'm too shy and terrified\033[0m\n");
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
