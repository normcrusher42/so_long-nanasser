#include "so_long_bonus.h"

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

void	initialize_tiles(t_data *data)
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
			"assets/textures/obstacle.xpm", &size.exitx, &size.exity);
	data->textures[6] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/exit_1.xpm", &size.exitx, &size.exity);
	data->textures[7] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/textures/exit_2.xpm", &size.exitx, &size.exity);
}

int	load_frames(t_data *data)
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
	return (0);
}
