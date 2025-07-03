#include "so_long_bonus.h"

// Deletes \n & \r at end of string
static void	del_newline(char *line)
{
	size_t		len;

	len = ft_strlen(line) - 1;
	if (len > 0 && (line[len] == '\n' || line[len] == '\r'))
		line[len] = '\0';
	if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[len - 1] = '\0';
}

// Checks if map is rectangular with right charactes
static void	check_line(char *line, char **map, int fd)
{
	static int	map_len = -1;
	int			row_len;
	int			i;

	i = -1;
	row_len = 0;
	del_newline(line);
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'P' && line[i] != 'E'
			&& line[i] != 'C' && line[i] != 'O')
			error_out('L', map, line, fd);
		row_len++;
	}
	if (row_len == 0)
		error_out('H', map, line, fd);
	else if (map_len == -1)
		map_len = row_len;
	if (map_len != row_len)
		error_out('X', map, line, fd);
}

// Reallocates map parsing
static char	**map_update(char **map, char *line, int size)
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
	if (!line)
	{
		free_map(new_map, NULL, -1);
		return (NULL);
	}
	new_map[i++] = ft_strdup(line);
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

// The main map parser
char	**map_reader(char *file_path, t_data *data)
{
	int		fd;
	int		height;
	char	*line;
	char	**map;

	map = NULL;
	height = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0 || filetype_check(file_path) == 0)
		error_out('D', NULL, NULL, -1);
	line = get_next_line(fd);
	while (line)
	{
		check_line(line, map, fd);
		map = map_update(map, line, height++);
		if (!map)
			error_out('M', map, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (height == 0 || !map)
		error_out('H', NULL, line, fd);
	validate_map(map, data);
	close(fd);
	return (map);
}
