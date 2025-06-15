#include "so_long.h"

// Duplicates the temporary map
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
	i = -1;
	while (map[++i])
		map_cpy[i] = ft_strdup(map[i]);
	map_cpy[i] = NULL;
	return (map_cpy);
}

// Fills the map like a bucket of water
void	flood_fill(char **map, t_map coords)
{
	int	height;
	int	width;

	height = 0;
	width = ft_strlen(map[0]);
	while (map[height])
		height++;
	if (coords.x < 0 || coords.y < 0 || coords.x >= width || coords.y >= height
		|| map[coords.y][coords.x] == '1' || map[coords.y][coords.x] == 'X')
		return ;
	map[coords.y][coords.x] = 'X';
	flood_fill(map, (t_map){coords.x + 1, coords.y});
	flood_fill(map, (t_map){coords.x - 1, coords.y});
	flood_fill(map, (t_map){coords.x, coords.y + 1});
	flood_fill(map, (t_map){coords.x, coords.y - 1});
}

// Locates (only one of) the player's position for flood_fill to initialize
void	find_player(char **map, t_map *coords)
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
				coords->y = i;
				coords->x = j;
				only_player(map);
				return ;
			}
			j++;
		}
	}
	if (player == 0 || coords->x == -1 || coords->y == -1)
		error_out('P', map, NULL, -1);
}

// Checks if flood filled C and E
bool	goals_reachable(char **map_cpy)
{
	int	i;
	int	j;

	i = -1;
	while (map_cpy[++i])
	{
		j = 0;
		while (map_cpy[i][j])
		{
			if (map_cpy[i][j] == 'C' || map_cpy[i][j] == 'E')
				return (false);
			j++;
		}
	}
	return (true);
}
