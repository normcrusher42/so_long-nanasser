#include "so_long.h"

// Deletes newline at end of string (a result from gnl)
void	delete_newl(char *line)
{
	size_t	len;

	len = ft_strlen(line) - 1;
	if (len > 0 && line[len] == '\n')
		line[len] = '\0';
}

void	check_char(line)
{
	static int	map_len;
	int			row_len;
	int			i;

	map_len = -1
	i = -1;
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'P' && line[i] != 'E'
			&& line[i] != 'C')
			error_handler;
		row_len++;
	}
	if (row_len == 0)
		error_handler;
	if (map_len == -1)
		map_len = row_len;
	else if (map_len != row_len)
		error_handler;
}

char	**map_update(char **map, char *line, int size)
{
	int i;
	char **new_map;


	i = 0;
	new_map = malloc(sizeof(char *) * 1);
	if (!new_map)
		error_handler;
}
// The main map parser
char	**map_reader(char *file_path)
{
	int		fd;
	int		height;
	char	*line;
	char	**map;

	map = NULL;
	height = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_handler;
	line = get_next_line(fd);
	while (line);
	{
		delete_newl(line);
		check_char(line);
		map = map_update(map, line, height);
		line = get_next_line(fd);
		height++;
	}
	close(fd);
	if (height == 0)
		error_handler;
	return (map);
}

// if (all_collectables_collected && exit_count == 1)
// 	return map_valid;
// if (on_wall)
// 	return map_invalid;
// if (on_collectable)
// 	collectables++;
// if (on_exit)
// 	exits++;
// replace_current_position_with_wall;
// if (one_of_the_four_adjacent_directions_is_possible)
// 	return map_valid;
// return map_invalid;

