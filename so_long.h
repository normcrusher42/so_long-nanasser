#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"
# include <stdio.h>
# include "mlx/mlx.h"
# include <stdbool.h>

// Map position //
typedef struct s_map
{
	int	x;
	int	y;
}	t_map;

// Error Handlers //
void		error_out(char error_sign, char **map, char *line, int fd);
void		free_map(char **map, char *line, int fd);

//-----------------------//
//   Map Parsing tools   //
//-----------------------//
char		**map_reader(char *file_path);
char		**dup_map(char **map);

// Map Validator //
int			filetype_check(char *filename);
void		validate_map(char **map);
void		find_player(char **map, t_map *coords);
void		flood_fill(char **map, t_map coords);
bool		goals_reachable(char **map_cpy);
void		only_player(char **map);



// typedef struct s_data
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	void		*textures[5];
// 	// t_map		*map;
// }	t_data;

#endif