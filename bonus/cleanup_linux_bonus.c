#include "so_long_bonus.h"

// Destroys all sprite images defined (hard-coded)
void	clean_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (data->textures[i])
		{
			mlx_destroy_image(data->mlx_ptr, data->textures[i]);
			data->textures[i] = NULL;
		}
		i++;
	}
	i = 0;
	while (i < 12)
	{
		if (data->frames[i])
		{
			mlx_destroy_image(data->mlx_ptr, data->frames[i]);
			data->frames[i] = NULL;
		}
		i++;
	}
}

// Cleanup following program exit but with conditions for mlx functions
void	exit_cleanup(t_data *data, int tick)
{
	clean_sprites(data);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (tick)
	{
		free_map(data->map, NULL, -1);
		if (!data->collectable)
		{
			ft_printf("\033[0;32mEpic Saga Complete!\033[0;37m\n");
			ft_printf("Only took like [\033[1;33m%d\033[0;37m] steps!\n",
				data->moves);
		}
		else
		{
			ft_printf("Saga not completed.. :(\n");
			ft_printf("You only had [\033[1;33m%d\033[0;37m] Fruits left...\n",
				data->collectable);
		}
		exit(0);
	}
}

// Main exit cleanup function (and mlx cleaner)
int	close_window(t_data *data, int tick)
{
	if (data->mlx_ptr && data->win_ptr)
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
	exit_cleanup(data, tick);
	return (0);
}
