#include "so_long_bonus.h"

// Animations for the exit tile and obstacles
void	exit_anim_bonus(t_data *data)
{
	if (!data->collectable)
	{
		if (++data->exit_anim_tick >= 1200)
		{
			data->exit_anim_tick = 0;
			data->exit_anim = 1 - data->exit_anim;
			draw_tile(data, 0, data->exitx, data->exity);
			draw_tile(data, 5 + data->exit_anim, data->exitx, data->exity);
		}
	}
}

// Animations for the obstacles
void	obstacle_anim(t_data *data)
{
	int	i;

	i = 0;
	if (++data->obstacle_anim_tick >= 1500)
	{
		data->obstacle_anim_tick = 0;
		data->obstacle_anim = (data->obstacle_anim + 1) % 4;
		while (i < data->obstacle_count)
		{
			draw_tile(data, 0, data->obstacles[i].x, data->obstacles[i].y);
			draw_tile_obstacle(data, 0 + data->obstacle_anim,
				data->obstacles[i].x, data->obstacles[i].y);
			i++;
		}
	}
}
