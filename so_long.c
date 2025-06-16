#include "so_long.h"

// int	destroy_process(t_data *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	mlx_destroy_display(data->mlx_ptr);
// 	free(data->mlx_ptr);
// 	return (0);
// }

void	ready_map(t_data *data, char *file)
{
	data->map = map_reader(file);
	if (!data->map)
		error_out('M', NULL, NULL, -1);
}

void	ready_window_render(t_data *data)
{
	tile_size(data);
	get_map_size(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img_width * data->mapx, data->img_height * data->mapy, "ITS ALIIIIIIVE >:D");
	// data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Front/Front0.xpm", &data->img_width, &data->img_height);
	// data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/floor.xpm", &data->img_width, &data->img_height);
	// data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/walls.xpm", &data->img_width, &data->img_height);
	// if (!data.textures[0] || !data.textures[0])
	// 		return (1);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		t_data	data;

		data.mlx_ptr = mlx_init();
		if (!data.mlx_ptr)
			return (1);
		ready_map(&data, av[1]);
		ready_window_render(&data);
		if (!data.win_ptr)
			return (free(data.mlx_ptr), 1);
		mlx_loop(data.mlx_ptr);
		return (0);
	}
	else
		perror("skill issue LMFAOOO");
	return (1);
}

// int	main(int ac, char **av)
// {
// 	int		i;
// 	char	**map;

// 	if (ac == 2)
// 	{
// 		i = 0;
// 		map = map_reader(av[1]);
// 		if (!map)
// 			error_out('M', NULL, NULL, -1);
// 		while (map[i])
// 			ft_printf("%s\n", map[i++]);
// 		free_map(map, NULL, -1);
// 	}
// 	return (0);
// }
