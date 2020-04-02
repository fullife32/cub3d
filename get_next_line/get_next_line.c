/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:48:53 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/02 17:09:03 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	clean(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	static t_buff	lst;
	int				nread;

	*line = NULL;
	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0)
		return (clean(line));
	if (ft_strclen(lst.buff, '\0') > 0)
		if (!(*line = ft_strcjoin(*line, lst.buff)))
			return (clean(line));
	while (ft_strclen(lst.buff, '\n') == -1)
	{
		if ((nread = read(fd, lst.buff, BUFFER_SIZE)) < 0)
			return (clean(line));
		lst.buff[nread] = '\0';
		if (!(*line = ft_strcjoin(*line, lst.buff)))
			return (clean(line));
		if (nread == 0)
			return (0);
	}
	nread = ft_strclen(lst.buff + ft_strclen(lst.buff, '\n'), '\0') + 1;
	ft_memcmove(lst.buff, lst.buff + ft_strclen(lst.buff, '\n') + 1, nread);
	return (1);
}
