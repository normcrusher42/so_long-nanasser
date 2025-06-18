#include "so_long.h"

// int	destroy_process(t_data *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	mlx_destroy_display(data->mlx_ptr);
// 	free(data->mlx_ptr);
// 	return (0);
// }

void	draw_tile(t_data *data, int	tile, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[tile], x * data->img_width, y * data->img_height);
}
int		get_tile_index(char c)
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

void	ready_map(t_data *data, char *file)
{
	data->map = map_reader(file, data);
	if (!data->map)
		error_out('M', NULL, NULL, -1);
}

void	ready_window_render(t_data *data)
{
	t_size	size;

	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/floor.xpm", &data->img_height, &data->img_height);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/wall.xpm", &size.wallx, &size.wally);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Front/Front0.xpm", &size.playerx, &size.playery);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/collectable.xpm", &size.collectablex, &size.collectabley);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/exit.xpm", &size.exitx, &size.exity);
	if (!data->textures[0] || !data->textures[1] || !data->textures[2] || !data->textures[3] || !data->textures[4])
			error_out('S', data->map, NULL, -1);
	draw_map(data);
}

// void	finish_game(t_data *data)
// {

// }

void	move_player(t_data *data, int x, int y)
{
	int	new_posx;
	int	new_posy;

	new_posx = data->playerx + x;
	new_posy = data->playery + y;
	if (data->map[new_posy][new_posx] != '1')
	{
		if (data->map[new_posy][new_posx] == 'E' && data->collectable)
			return ;
		else if (data->map[new_posy][new_posx] == 'C')
		{
			data->collectable--;
			draw_tile(data, 0, new_posx, new_posy);
		}
		else if (data->map[new_posy][new_posx] == 'E' && !data->collectable)
			close_window(data);
		draw_tile(data, 0, data->playerx, data->playery);
		data->map[data->playery][data->playerx] = '0';
		data->playery = new_posy;
		data->playerx = new_posx;
		data->map[data->playery][data->playerx] = 'P';
		draw_tile(data, 2, data->playerx, data->playery);
		ft_printf("Current step is [%d]\n", ++data->moves);
	}
}

int		key_press(int key, t_data *data)
{
	if (key == ESC)
		close_window(data);
	else if (key == UP || key == W)
		move_player(data, 0, -1);
	else if (key == LEFT || key == A)
		move_player(data, -1, 0);
	else if (key == DOWN || key == S)
		move_player(data, 0, 1);
	else if (key == RIGHT || key == D)
		move_player(data, 1, 0);
	data->moveready = 0;
	return (0);
}

int game_loop(void *param)
{
    t_data *data = (t_data *)param;

    if (!data->moveready)
    {
        data->movedelay++;
        if (data->movedelay >= 1000) // adjust based on frame speed
        {
            data->moveready = 1;
            data->movedelay = 0;
        }
    }
    return (0);
}

void	hooks_config(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
}

void	create_window(t_data *data)
{
	tile_size(data);
	get_map_size(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img_width * data->mapx, data->img_height * data->mapy, "ITS ALIIIIIIVE >:D");
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		error_out('S', data->map, NULL, -1);
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		t_data	data;

		data = (t_data){0};
		ready_map(&data, av[1]);
		data.mlx_ptr = mlx_init();
		if (!data.mlx_ptr)
			return (1);
		create_window(&data);
		hooks_config(&data);
		ready_window_render(&data);
		mlx_loop(data.mlx_ptr);
		return (0);
	}
	else
		perror("\033[0;31mskill issue LMFAOOO");
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
