#include "so_long.h"

// Deletes newline at end of string and checks if its rectangular (and while including the right characters)
void	check_line(char *line)
{
	static int	map_len;
	int			row_len;
	int			i;
	size_t		len;

	i = -1;
	map_len = -1;
	len = ft_strlen(line) - 1;
	if (len > 0 && line[len] == '\n')
		line[len] = '\0';
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'P' && line[i] != 'E'
			&& line[i] != 'C')
			error_out('l');
		row_len++;
	}
	if (row_len == 0)
		error_out('h');
	if (map_len == -1)
		map_len = row_len;
	else if (map_len != row_len)
		error_out('x')
}
// Reallocates map parsing
char	**map_update(char **map, char *line, int size)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = malloc(sizeof(char *) * (size + 2));
	if (!new_map)
		return (NULL);
	while (i < size)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i++] = ft_strdup(line);
	new_map[i] = NULL;
	free(map);
	return (new_map);
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
		error_out('d');
	line = get_next_line(fd);
	while (line)
	{
		check_line(line);
		map = map_update(map, line, height++);
		if (!map)
			error_out('m');
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (height == 0)
		error_out('h');
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
