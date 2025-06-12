/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:46:33 by nanasser          #+#    #+#             */
/*   Updated: 2025/06/12 16:52:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Buffersize definition
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

// Singly Linked list struct
typedef struct s_listt
{
	char			*content;
	struct s_listt	*next;
}	t_listt;

char	*get_next_line(int fd);
t_listt	*ft_lstlast_gnl(t_listt *lst);
void	ft_lstclear_gnl(t_listt **lst, t_listt *new_node, char *buf);
int		find_newline(t_listt *list);
void	new_lst(t_listt **list, int fd);
void	ft_lstjoin(t_listt **list, char *buf);
int		len_to_nline(t_listt *list);
char	*get_line(t_listt *list);
void	str_cpy(t_listt *list, char *str);
void	cleanup(t_listt **list);

#endif

/* FD access modes:
O_RDONLY	Open for reading only
O_WRONLY	Open for writing only
O_RDWR		Open for reading and writing
O_CREAT		Create file if it does not exist
O_TRUNC		Truncate file to 0 length if it exists
O_APPEND	Append to the end of the file 
*/
