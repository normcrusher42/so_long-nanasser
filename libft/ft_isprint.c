/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:49:51 by nanasser          #+#    #+#             */
/*   Updated: 2025/05/27 04:32:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int word)
{
	if (word >= 32 && word <= 126)
		return (1);
	return (0);
}
