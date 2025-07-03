#include "so_long.h"

// Simply calls map parser to main
static void	ready_map(t_data *data, char *file)
{
	data->map = map_reader(file, data);
	if (!data->map)
		error_out('M', NULL, NULL, -1);
}

// Gets floor size and initializes window without manually defining it
static void	create_window(t_data *data)
{
	tile_size(data);
	get_map_size(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img_width * data->mapx,
			data->img_height * data->mapy, "EPIC: The Game");
	if (!data->win_ptr)
	{
		close_window(data, 0);
		error_out('S', data->map, NULL, -1);
	}
}

// le Magie 𝓬𝓸𝓶𝓶𝓮𝓷𝓬𝓮
int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		data = (t_data){0};
		ready_map(&data, av[1]);
		data.mlx_ptr = mlx_init();
		if (!data.mlx_ptr)
			error_out('M', data.map, NULL, -1);
		create_window(&data);
		hooks_config(&data);
		ready_window_render(&data);
		mlx_loop(data.mlx_ptr);
	}
	ft_putendl_fd("\033[1;31mError\033[0;31m", 2);
	if (ac < 2)
		ft_putendl_fd("This ain't the piscine btw, add a program argument", 2);
	else if (ac > 2)
		ft_putendl_fd("Too many arguments!! Only 1 is needed.", 2);
	return (1);
}
