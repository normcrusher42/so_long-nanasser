#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"
# include <stdio.h>
# include "mlx/mlx.h"

// Error Handlers //
void	error_out(char error_sign, char **map, char *line, int fd);
char	**map_reader(char *file_path);
char	**map_update(char **map, char *line, int size);
void	free_map(char **map, char *line, int fd);

// typedef struct s_data
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	void		*textures[5];
// 	// t_map		*map;
// }	t_data;

#endif