#include "so_long_bonus.h"

// Initializes the frames for the player animations
static void	initialize_frames(const char **frames)
{
	frames[0] = "assets/textures/Front/Front0.xpm";
	frames[1] = "assets/textures/Front/Front1.xpm";
	frames[2] = "assets/textures/Front/Front2.xpm";
	frames[3] = "assets/textures/Left/Left0.xpm";
	frames[4] = "assets/textures/Left/Left1.xpm";
	frames[5] = "assets/textures/Left/Left2.xpm";
	frames[6] = "assets/textures/Right/Right0.xpm";
	frames[7] = "assets/textures/Right/Right1.xpm";
	frames[8] = "assets/textures/Right/Right2.xpm";
	frames[9] = "assets/textures/Back/Back0.xpm";
	frames[10] = "assets/textures/Back/Back1.xpm";
	frames[11] = "assets/textures/Back/Back2.xpm";
}

// Initializes the textures for the game tiles
static void	initialize_tiles(t_data *data)
{
	t_size	size;

	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/floor.xpm", &data->img_height, &data->img_height);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/wall.xpm", &size.wallx, &size.wally);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/Front/Front0.xpm", &size.playerx, &size.playery);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/collectable.xpm", &size.collectablex,
			&size.collectabley);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/exit.xpm", &size.exitx, &size.exity);
	data->textures[5] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/exit_1.xpm", &size.exitx, &size.exity);
	data->textures[6] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/exit_2.xpm", &size.exitx, &size.exity);
	if (!data->textures[0] || !data->textures[1] || !data->textures[2]
		|| !data->textures[3] || !data->textures[4] || !data->textures[5]
		|| !data->textures[6])
	{
		close_window(data, 0);
		error_out('S', data->map, NULL, -1);
	}
}

// Initializes the obstacle animations
static void	init_obstacle_anim(t_data *data)
{
	t_size	size;

	data->obstacle[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/Obstacle0.xpm", &size.wallx, &size.wally);
	data->obstacle[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/Obstacle1.xpm", &size.wallx, &size.wally);
	data->obstacle[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/Obstacle2.xpm", &size.wallx, &size.wally);
	data->obstacle[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/Obstacle3.xpm", &size.wallx, &size.wally);
	if (!data->obstacle[0] || !data->obstacle[1] || !data->obstacle[2]
		|| !data->obstacle[3])
	{
		close_window(data, 0);
		error_out('S', data->map, NULL, -1);
	}
}

// Loads the default tile theme for the game
void	default_tile_theme(t_data *data)
{
	int			i;
	int			w;
	int			h;
	const char	*frames[12];

	initialize_frames(frames);
	i = -1;
	while (++i < 12)
	{
		data->frames[i] = mlx_xpm_file_to_image(data->mlx_ptr,
				(char *)frames[i], &w, &h);
		if (!data->frames[i])
		{
			close_window(data, 0);
			error_out('S', data->map, NULL, -1);
		}
	}
	initialize_tiles(data);
	init_obstacle_anim(data);
	count_obstacle(data);
	save_obstacles(data);
}
