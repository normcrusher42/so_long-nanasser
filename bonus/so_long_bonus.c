#include "so_long_bonus.h"

// Defining the needed variables to help make the smooth tile animation work
static void	set_variables(t_data *data)
{
	data->smooth_x = data->playerx * data->img_width;
	data->smooth_y = data->playery * data->img_height;
	data->target_x = data->smooth_x;
	data->target_y = data->smooth_y;
	data->moving = 0;
	data->move_speed = 8;
	data->step_log = 0;
}

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

// just a silly exit error message for lengthy/short args
static void	silly_arg_error(int ac)
{
	ft_putendl_fd("\033[1;31mError\033[0;31m", 2);
	if (ac < 2)
		ft_putendl_fd("This ain't the piscine btw, add a program argument", 2);
	else if (ac > 3)
		ft_putendl_fd("Too many arguments!! At least 2 is needed.", 2);
	exit(1);
}

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

// le Magie 𝓬𝓸𝓶𝓶𝓮𝓷𝓬𝓮
int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2 || ac == 3)
	{
		data = (t_data){0};
		ready_map(&data, av[1]);
		data.mlx_ptr = mlx_init();
		if (!data.mlx_ptr)
			error_out('M', data.map, NULL, -1);
		create_window(&data);
		set_variables(&data);
		hooks_config(&data);
		if (ac == 3)
			map_theme(&data, av[2]);
		else
			default_tile_theme(data);
		draw_map(data);
		display_status(&data);
		mlx_loop(data.mlx_ptr);
		return (0);
	}
	silly_arg_error(ac);
}
