#include "so_long_bonus.h"

void	animation_sequence(t_data *data)
{
	int	w;
	int	h;
	data->frames[0] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Front/Front0.xpm", &w, &h);
	data->frames[1] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Front/Front1.xpm", &w, &h);
	data->frames[2] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Front/Front2.xpm", &w, &h);
	data->frames[3] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Left/Left0.xpm", &w, &h);
	data->frames[4] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Left/Left1.xpm", &w, &h);
	data->frames[5] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Left/Left2.xpm", &w, &h);
	data->frames[6] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Right/Right0.xpm", &w, &h);
	data->frames[7] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Right/Right1.xpm", &w, &h);
	data->frames[8] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Right/Right2.xpm", &w, &h);
	data->frames[9] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Back/Back0.xpm", &w, &h);
	data->frames[10] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Back/Back1.xpm", &w, &h);
	data->frames[11] = mlx_xpm_file_to_image(data->mlx_ptr, "assets/textures/Back/Back2.xpm", &w, &h);
}
