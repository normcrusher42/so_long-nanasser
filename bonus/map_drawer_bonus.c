#include "so_long_bonus.h"

// Loads the theme based on the argument given
void	map_theme(t_data *data, char *theme)
{
	if (!ft_strncmp(theme, "sea", 3) || !ft_strncmp(theme, "Sea", 3))
		sea_tile_theme(data);
	else if (!ft_strncmp(theme, "winion", 6) || !ft_strncmp(theme, "Winion", 6)
		|| !ft_strncmp(theme, "Winion island", 13)
		|| !ft_strncmp(theme, "island", 6)
		|| !ft_strncmp(theme, "Island", 6))
		default_tile_theme(data);
	else
	{
		ft_printf("Unknown Theme. Using default: \"Winion island\"\n");
		default_tile_theme(data);
	}
}

// Draws the tile at the given coordinates
void	draw_tile(t_data *data, int tile, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[tile],
		x * data->img_width, y * data->img_height);
}

// Draws the obstacle tile at the given coordinates
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
			if (i == -1)
				draw_tile_obstacle(data, 0, x, y);
			else if (i)
				draw_tile(data, i, x, y);
		}
	}
	draw_tile(data, 2, data->playerx, data->playery);
}
