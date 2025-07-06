#include "so_long.h"

// Self-explanatory. Needed for map size * floor size.
void	get_map_size(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (data->map[y])
		y++;
	while (data->map[y - 1][x])
		x++;
	if (x > 51 || y > 27)
	{
		close_window(data, 0);
		error_out('1', data->map, NULL, -1);
	}
	data->mapx = x;
	data->mapy = y;
}

// Extracts XPM size definition via ft_split & atoi
static void	check_width_height(char *line, t_data *data, int fd)
{
	char	**num;

	if (line[0] == '\n')
	{
		close_window(data, 0);
		error_out('S', data->map, line, fd);
	}
	line[0] = ' ';
	num = ft_split((const char *)line, ' ');
	if (!num || !num[1] || ft_atoi(num[0]) <= 0 || ft_atoi(num[1]) <= 0)
	{
		close_window(data, 0);
		free_map(data->map, NULL, -1);
		error_out('S', num, line, fd);
	}
	data->img_width = ft_atoi(num[0]);
	data->img_height = ft_atoi(num[1]);
	if (data->img_width <= 0 || data->img_height <= 0)
	{
		close_window(data, 0);
		free_map(data->map, NULL, -1);
		error_out('S', num, line, fd);
	}
	free_map(num, NULL, -1);
}

// Goes to 4th line where XPM size definition normally is
static void	get_tile_size_from_xpm(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close_window(data, 0);
		error_out('S', data->map, NULL, -1);
	}
	while (++i <= 4)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n' || line[0] == '\r')
			break ;
		if (i == 4 && line)
		{
			check_width_height(line, data, fd);
			break ;
		}
		free(line);
	}
	free_map(NULL, line, fd);
	close(fd);
}

// Defines window size based on floor tile size
void	tile_size(t_data *data)
{
	get_tile_size_from_xpm("assets/textures/floor.xpm", data);
	if (data->img_width <= 0 || data->img_height <= 0)
	{
		close_window(data, 0);
		error_out('S', data->map, NULL, -1);
	}
}
