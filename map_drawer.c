#include "so_long.h"

// Animations for the exit tile and obstacles
void	exit_anim(t_data *data)
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

// returns tile defintion to draw
int	get_tile_index(char c)
{
	if (c == '1')
		return (1);
	else if (c == 'P')
		return (2);
	else if (c == 'C')
		return (3);
	else if (c == 'E')
		return (4);
	return (0);
}

// Self-Explanatory.
void	draw_tile(t_data *data, int tile, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[tile],
		x * data->img_width, y * data->img_height);
}

// Self-Explanatory. 
void	draw_map(t_data *data)
{
	int	x;
	int	y;
	int	i;

	y = -1;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			draw_tile(data, 0, x, y);
			i = get_tile_index(data->map[y][x]);
			if (i)
				draw_tile(data, i, x, y);
		}
	}
}

// Store Textures into the texture array and draws the map
void	ready_window_render(t_data *data)
{
	t_size	size;

	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/floor.xpm", &data->img_height, &data->img_height);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/wall.xpm", &size.wallx, &size.wally);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/Front/Front0.xpm", &size.playerx, &size.playery);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/collectable.xpm", &size.collectablex,
			&size.collectabley);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/exit.xpm", &size.exitx, &size.exity);
	data->textures[5] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/exit_1.xpm", &size.exitx, &size.exity);
	data->textures[6] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/exit_2.xpm", &size.exitx, &size.exity);
	if (!data->textures[0] || !data->textures[1] || !data->textures[2]
		|| !data->textures[3] || !data->textures[4] || !data->textures[5]
		|| !data->textures[6])
	{
		close_window(data, 0);
		error_out('S', data->map, NULL, -1);
	}
	draw_map(data);
}
