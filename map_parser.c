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
		error_out('m');
	i = 0;
	while (map[i])
		map_cpy[i] = ft_strdup(map[i]);
	map_cpy[i] = NULL;
	return (map_cpy);
}

void	map_validity(char **map)
{
	int	i;
	int	j;
	int	end;

	i = -1;
	j = 0;
	end = ft_strlen(map[0]);
	while (map[++i])
	{
		j = 0;
		if (i == 0 || map[i + 1] != NULL)
		{
			while (j < end)
			{
				if (map[i][j++] != '1')
					error_out('m'); // <---- I give up just handle the fucking leaks later
			}
		}
		else if (map[i][0] != '1' || map[i][end - 1] != '1')
			error_out('m');
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
static void	check_line(char *line)
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
			error_out('l');
		row_len++;
	}
	if (row_len == 0)
		error_out('h');
	else if (map_len == -1)
		map_len = row_len;
	if (map_len != row_len)
		error_out('x');
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
		return (NULL);
	new_map[i++] = ft_strdup(line);
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

void	map_de_map(char *line, char ***map, int *height)
{
	char	**updated;

	check_line(line);
	updated = map_update(*map, line, *height);
	if (!updated)
		error_out('m');
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
		error_out('d');
	line = get_next_line(fd);
	while (line)
	{
		map_de_map(line, &map, &height);
		line = get_next_line(fd);
	}
	close(fd);
	if (height == 0 || !map)
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
