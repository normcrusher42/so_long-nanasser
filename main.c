#include "so_long.h"

// int	destroy_process(t_data *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	mlx_destroy_display(data->mlx_ptr);
// 	free(data->mlx_ptr);
// 	return (0);
// }

// int	main(void)
// {
// 	t_data	data;

// 	data.mlx_ptr = mlx_init();
// 	if (!data.mlx_ptr)
// 		return (1);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 800, "ITS ALIIIIIIVE >:D");
// 	if (!data.win_ptr)
// 		return (free(data.mlx_ptr), 1);
// 	mlx_loop(data.mlx_ptr);
// 	// mlx_hook(data.win_ptr, )
// }

void	free_map(char **map, char *line, int fd)
{
	int	i;

	i = 0;
	if (line)
	{
		free(line);
		line = get_next_line(fd);
		while (line)
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	if (map)
	{
		while (map[i])
			free(map[i++]);
		free(map);
	}
}

int	main(int ac, char **av)
{
	int		i;
	char	**map;

	if (ac == 2)
	{
		i = 0;
		char = map_reader(av[1]);
		if (!map)
			error_out('M', NULL, NULL, -1);
		while (map[i])
			ft_printf("%s\n", map[i++]);
		free_map(map, NULL, -1);
	}
	return (0);
}
