#include "so_long.h"

// int	destroy_process(t_data *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	mlx_destroy_display(data->mlx_ptr);
// 	free(data->mlx_ptr);
// 	return (0);
// }

void	draw_tiles(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	while (data->map[y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[1], x * data->img_width, y * data->img_height);
			if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[0], x * data->img_width, y * data->img_height);
			else if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[2], x * data->img_width, y * data->img_height);
			else if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[3], x * data->img_width, y * data->img_height);
			else if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[4], x * data->img_width, y * data->img_height);
		}
		y++;
	}
}

void	ready_map(t_data *data, char *file)
{
	data->map = map_reader(file);
	if (!data->map)
		error_out('M', NULL, NULL, -1);
}

void	ready_window_render(t_data *data)
{
	t_size	size;

	tile_size(data);
	get_map_size(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img_width * data->mapx, data->img_height * data->mapy, "ITS ALIIIIIIVE >:D");
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		error_out('S', data->map, NULL, -1);
	}
	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Front/Front0.xpm", &size.playerx, &size.playery);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/floor.xpm", &data->img_height, &data->img_height);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/wall.xpm", &size.wallx, &size.wally);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/collectable.xpm", &size.collectablex, &size.collectabley);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/exit.xpm", &size.exitx, &size.exity);
	ft_printf("width : [%d]\nheight : [%d]\n", data->img_width, data->img_height);
	if (!data->textures[0] || !data->textures[1] || !data->textures[2] || !data->textures[3] || !data->textures[4])
			error_out('S', data->map, NULL, -1);
	draw_tiles(data);
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
		mlx_loop(data.mlx_ptr);
		free(data.mlx_ptr);
		free(data.win_ptr);
		free_map(data.map, NULL, -1);
		return (0);
	}
	else
		perror("skill issue LMFAOOO\n");
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
