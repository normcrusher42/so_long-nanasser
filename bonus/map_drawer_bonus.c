#include "so_long_bonus.h"

// Self-Explanatory.
void	draw_tile(t_data *data, int tile, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[tile],
		x * data->img_width, y * data->img_height);
}

void	draw_tile_obstacle(t_data *data, int tile, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->obstacle[tile],
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
			i = get_tile_index_bonus(data->map[y][x]);
			if (i)
				draw_tile(data, i, x, y);
		}
	}
	draw_tile(data, 2, data->playerx, data->playery);
}
