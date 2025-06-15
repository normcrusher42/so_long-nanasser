#include "so_long.h"

// Ensures there's only one player
void	only_player(char **map)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	player = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				if (player++)
					error_out('P', map, NULL, -1);
			}
			j++;
		}
	}
}

// Checks if collectables and exit condition is valid
static void	find_goals(char **map)
{
	int	i;
	int	j;
	int	collectable;
	int	exit;

	i = -1;
	exit = 0;
	collectable = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				collectable++;
			else if (map[i][j] == 'E')
				exit++;
			j++;
		}
	}
	if (collectable == 0 || exit == 0 || exit > 1)
		error_out('G', map, NULL, -1);
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

// Checks if map is enclosed
static void	map_check(char **map)
{
	int		i;
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

// The main map validation function for if its playable
void	validate_map(char **map)
{
	t_map	coords;
	char	**map_cpy;

	coords.x = -1;
	coords.y = -1;
	map_check(map);
	find_player(map, &coords);
	find_goals(map);
	map_cpy = dup_map(map);
	flood_fill(map_cpy, coords);
	if (!goals_reachable(map_cpy))
	{
		free_map(map, NULL, -1);
		error_out('G', map_cpy, NULL, -1);
	}
	free_map(map_cpy, NULL, -1);
}
