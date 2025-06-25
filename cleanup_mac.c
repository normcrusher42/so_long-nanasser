#include "so_long.h"

// Cleanup following program exit but with conditions for mlx functions
void	exit_cleanup(t_data *data, int tick)
{
	clean_sprites(data);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	if (tick)
	{
		free_map(data->map, NULL, -1);
		exit(0);
	}
}

// Main exit cleanup function (and mlx cleaner)
int	close_window(t_data *data, int tick)
{
	if (data->mlx_ptr && data->win_ptr)
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
	exit_cleanup(data, tick);
	return (0);
}
