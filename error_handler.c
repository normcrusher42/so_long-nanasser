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
	if (error_sign == 'D') // file descriptor failed to open
		perror("\033[1;31mMap failed to open. Bad input? Typo? Perhaps a SKILL ISSUE");
	else if (error_sign == 'S') // sprite size parsing failed
		perror("\033[0;31mGot the right .xpm format m8?");
	else if (error_sign == 'M') // map failed to allocate
		perror("\033[1;31mWoops, something went wrong with the process. Maybe try again? Or let Nasser fix his shit code.");
	else if (error_sign == 'H') // height value too small
		perror("\033[1;31mThat's not how you imagine a map!!! Stop trying to break me and play the damn game \033[1;37mITS FREE");
	else if (error_sign == 'L') // Failed to read line due to an incorrect character conflict
		perror("\033[1;31mWrong character found in map. Write it according to the subject!!");
	else if (error_sign == 'X') // uneven map length.
		perror("\033[1;31mMap length uneven. Do you need a shape sorter to learn what a rectangle looks like?");
	else if (error_sign == '1') // map isn't enclosed
		perror("\033[1;31mMap isn't boxed properly, check your ones again");
	else if (error_sign == 'P') // no player/more than 1 player
		perror("\033[0;31mAre you the only one playing the game or not? Get a controller. Be. The. \033[1;31mPLAYER.");
	else if (error_sign == 'G') // no collectables and/or exit (or more than 1)
		perror("\033[1;31mAppreciate the attempt but your goals are just a teensy bit out of your reach if u get my drift.");
	else // dumbass used the wrong error handling sign for his own function
		perror("\033[0;31mbroskie u got the wrong error sign HOW DO YOU MESS THAT UP?????? \033[1;31mNO PLAYER EVER SEES THIS MESSAGE");
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
	if (data->textures[0])
	{
		while (i < 5)
		mlx_destroy_image(data->mlx_ptr, data->textures[i++]);
	}
}

void	exit_cleanup(t_data *data)
{
	clean_sprites(data);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map(data->map, NULL, -1);
	exit(0);
}

int	close_window(t_data *data)
{
	// mlx_clear_window(data->mlx_ptr, data->win_ptr);
	exit_cleanup(data);
	return (0);
}
