#include "so_long.h"

// int	destroy_process(t_data *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	mlx_destroy_display(data->mlx_ptr);
// 	free(data->mlx_ptr);
// 	return (0);
// }

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 800, "ITS ALIIIIIIVE >:D");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	mlx_loop(data.mlx_ptr);
	// mlx_hook(data.win_ptr, )
}
