/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/09 17:07:18 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	err(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	return (ERR);
}

int	res_parse(char *line, t_res *res)
{
	line++;
	while (*line == ' ')
		line++;
	res->width = ft_atoi(line);
	if (res->width > 1280)
		res->width = 1280;
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line == ' ')
		line++;
	res->height = ft_atoi(line);
	if (res->height > 720)
		res->height = 720;
	if (res->height <= 0 || res->width <= 0)
		return (ERR);
	return (OK);
}

int	map_parse(int fd, char *line, t_map *map)
{
	t_list	*first;
	t_list	*lst;
	int		i;

	first = NULL;
	if ((lst = ft_lstnew(line)) == NULL)
		return (ERR);
	ft_lstadd_back(&first, lst);
	while (get_next_line(fd, &line) > 0)
	{
		if ((lst = ft_lstnew(line)) == NULL)
			return (ERR);
		ft_lstadd_back(&first, lst);
	}
	if ((lst = ft_lstnew(line)) == NULL)
		return (ERR);
	ft_lstadd_back(&first, lst);
	i = 0;
	if ((map->map = malloc(sizeof(char *) * (ft_lstsize(first) + 1))) == NULL)
		return (ERR);
	lst = first;
	while (lst != NULL)
	{
		map->map[i] = lst->content;
		lst = lst->next;
		i++;
	}
	map->map[i] = NULL;
	// ft_lstclear(&first, (void *)ft_lstdelone);
	return (OK);
}

int	parse(int fd, t_res *res, t_txr *txr, t_clr *clr, t_map *map)
{
	char	*line;
	int		i;
	
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		printf("%s\n", line);
		while (line[i] == ' ')
			i++;
		if (line[i] == 'R')
			if (res_parse(line + i, res) == ERR)
				return (err(&line));
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			if (txr_parse(line[i], line + i, txr) == ERR)
				return (err(&line));
		if (line[i] == 'F' || line[i] == 'C')
			if (clr_parse(line[i], line + i, clr) == ERR)
				return (err(&line));
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
		{
			if (map_parse(fd, line, map) == ERR)
				return (err(&line));
			else
				return (OK);
		}
		err(&line);
	}
	return (OK);
}
