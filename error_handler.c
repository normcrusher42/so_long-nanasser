#include "so_long.h"

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

void	error_out(char error_sign, char **map, char *line, int fd)
{
	ft_putendl_fd("\033[1;31mError\033[0;31m", 2);
	if (error_sign == 'D')
		perror("Invalid Map. Bad input? Typo? Perhaps a SKILL ISSUE");
	else if (error_sign == 'S')
		perror("Got the right .xpm format m8?");
	else if (error_sign == 'M')
		perror("Woops, something died. Prolly allocation failure.");
	else if (error_sign == 'H')
		perror("Ur not slick, get the map format rite.");
	else if (error_sign == 'L')
		perror("Wrong character found in map. get it rite!11!1!!");
	else if (error_sign == 'X')
		perror("Map length uneven. Go back to Kindergarten.");
	else if (error_sign == '1')
		perror("Map isn't boxed properly, check your ones again");
	else if (error_sign == 'P')
		perror("Play the game bro its free Wallahi there's no transactions");
	else if (error_sign == 'G')
		perror("Ur goals are just a teensy bit out of your reach.");
	if (line)
		free_map(NULL, line, fd);
	if (map)
		free_map(map, NULL, -1);
	exit(1);
}

void	clean_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (data->textures[i])
		{
			mlx_destroy_image(data->mlx_ptr, data->textures[i]);
			data->textures[i] = NULL;
		}
		i++;
	}
}

// Cleanup exit
void	exit_cleanup(t_data *data, int tick)
{
	clean_sprites(data);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		if (!IS_MACOS)
			mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (tick)
	{
		free_map(data->map, NULL, -1);
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
