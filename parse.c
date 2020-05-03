/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 18:02:44 by eassouli          #+#    #+#             */
/*   Updated: 2020/05/03 03:42:38 by eassouli         ###   ########.fr       */
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
	if (res->width > 1920)
		res->width = 1920;
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line == ' ')
		line++;
	res->height = ft_atoi(line);
	if (res->height > 1080)
		res->height = 1080;
	if (res->height <= 0 || res->width <= 0)
		return (ERR);
	return (OK);
}

int	add_line(char *line, t_list	**first, t_list	**lst)
{
	if ((*lst = ft_lstnew(line)) == NULL)
		return (ERR);
	ft_lstadd_back(first, *lst);
	return (OK);
}

int	start_p(int y, char *line, t_plr *plr)
{
	int x;

	x = 0;
	while (line[x] != '\0')
	{
		if (line[x] == 'N' || line[x] == 'S' || line[x] == 'W' || line[x] == 'E')
		{
			if (plr->pos_x != 0)
				return (ERR);
			plr->pos_y = y + 0.5;
			plr->pos_x = x + 0.5;
		}
		if (line[x] == 'N')
			plr->dir_y = -1;
		else if (line[x] == 'S')
			plr->dir_y = 1;
		else if (line[x] == 'W')
			plr->dir_x = -1;
		else if (line[x] == 'E')
			plr->dir_x = 1;
		x++;
	}
	return (OK);
}

int	map_parse(int fd, char *line, t_map *map, t_plr *plr)
{
	t_list	*first;
	t_list	*lst;
	int		y;

	first = NULL;
	lst = NULL;
	if (add_line(line, &first, &lst) == ERR)
		return (ERR);
	while (get_next_line(fd, &line) > 0)
	{
		if (add_line(line, &first, &lst) == ERR)
		return (ERR);
	}
	if (add_line(line, &first, &lst) == ERR)
		return (ERR);
	y = 0;
	if ((map->map = malloc(sizeof(char *) * (ft_lstsize(first) + 1))) == NULL)
		return (ERR);
	lst = first;
	while (lst != NULL)
	{
		map->map[y] = lst->content;
		if (start_p(y, map->map[y], plr) == ERR)
			return (ERR);
		lst = lst->next;
		y++;
	}
	map->map[y] = NULL;
	// ft_lstclear(&first, (void *)ft_lstdelone);
	return (OK);
}

int	parse(int fd, t_res *res, t_txr *txr, t_clr *clr, t_map *map, t_plr *plr)
{
	char	*line;
	int		i;
	
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
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
			if (map_parse(fd, line, map, plr) == ERR)
				return (err(&line));
			else
				return (OK);
		}
		err(&line);
	}
	return (OK);
}
