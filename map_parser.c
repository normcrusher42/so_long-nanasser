#include "so_long.h"

char	**dup_map(char **map)
{
	int		i;
	char	**map_cpy;

	i = 0;
	while (map[i])
		i++;
	map_cpy = malloc(sizeof(char *) * (i + 1));
	if (!map_cpy)
		error_out('M', map, NULL, -1);
	i = 0;
	while (map[i])
		map_cpy[i] = ft_strdup(map[i]);
	map_cpy[i] = NULL;
	return (map_cpy);
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	path_validator(char **map)
{
	int	i;
	int	j;
	int

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j++])
		{
			if (map[i][j] == 'P')
			{
				
			}
		}
	}
}

static void	map_validity(char **map)
{
	int	i;
	size_t	j;
	size_t	end;

	i = -1;
	end = ft_strlen(map[0]);
	while (map[++i])
	{
		j = 0;
		if (i == 0 || !map[i + 1])
		{
			while (j < end)
			{
				if (map[i][j++] != '1')
					error_out('1', map, NULL, -1);
			}
		}
		else if (map[i][0] != '1' || map[i][end - 1] != '1')
			error_out('1', map, NULL, -1);
	}
}

// Checks if the filetype is '.ber'
int	filetype_check(char *filename)
{
	int	len;

	len = ft_strlen(filename) - 4;
	if (len < 5 || ft_strncmp(&filename[len], ".ber", 4) != 0)
		return (0);
	return (1);
}

void	del_newline(char *line)
{
	size_t		len;

	len = ft_strlen(line) - 1;
	if (len > 0 && (line[len] == '\n' || line[len] == '\r'))
		line[len] = '\0';
	if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[len - 1] = '\0';
}

// Deletes \n & \r at end of string and checks if its rectangular (and while including the right characters)
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
			&& line[i] != 'C')
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

void	map_de_map(char *line, char ***map, int *height, int fd)
{
	char	**updated;

	check_line(line, *map, fd);
	updated = map_update(*map, line, *height);
	if (!updated)
		error_out('M', *map, line, fd);
	*map = updated;
	(*height)++;
	free(line);
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
	fd = open(file_path, O_RDONLY);
	if (fd < 0 || filetype_check(file_path) == 0)
		error_out('D', NULL, NULL, -1);
	line = get_next_line(fd);
	while (line)
	{
		map_de_map(line, &map, &height, fd);
		line = get_next_line(fd);
	}
	if (height == 0 || !map)
		error_out('H', NULL, line, fd);
	map_validity(map);
	close(fd);
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
