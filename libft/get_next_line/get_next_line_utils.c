/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:46:36 by nanasser          #+#    #+#             */
/*   Updated: 2025/06/12 16:52:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_listt	*ft_lstlast_gnl(t_listt *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
	{
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lstclear_gnl(t_listt **lst, t_listt *new_node, char *buf)
{
	t_listt	*move;
	t_listt	*temp;

	if (!*lst)
		return ;
	move = *lst;
	while (move)
	{
		temp = move -> next;
		free(move -> content);
		move -> content = NULL;
		free(move);
		move = temp;
	}
	*lst = NULL;
	if (new_node -> content[0])
		*lst = new_node;
	else
	{
		free(buf);
		buf = NULL;
		free(new_node);
		new_node = NULL;
	}
}

int	find_newline(t_listt *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list -> content[i] && i < BUFFER_SIZE)
		{
			if (list -> content[i] == '\n')
				return (1);
			i++;
		}
		list = list -> next;
	}
	return (0);
}

int	len_to_nline(t_listt *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list -> content[i])
		{
			if (list -> content[i] == '\n')
				return (++len);
			i++;
			len++;
		}
		list = list -> next;
	}
	return (len);
}

void	str_cpy(t_listt *list, char *str)
{
	int	i;
	int	n;

	if (!list)
		return ;
	n = 0;
	while (list)
	{
		i = 0;
		while (list -> content[i])
		{
			if (list -> content[i] == '\n')
			{
				str[n] = '\n';
				str[++n] = '\0';
				return ;
			}
			str[n++] = list -> content[i++];
		}
		list = list -> next;
	}
	str[n] = '\0';
}
