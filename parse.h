/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 17:14:35 by eassouli          #+#    #+#             */
/*   Updated: 2020/04/06 17:06:52 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

#define ERR -1
#define OK 1

typedef struct	s_res
{
	int		width;
	int		height;
}				t_res;

typedef struct	s_txr
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
}				t_txr;

typedef struct	s_clr
{
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	char	*floor;
	char	*ceiling;
}				t_clr;

typedef struct	s_map
{
	char	**map;
}				t_map;


void	init(t_res *res, t_txr *txr, t_clr *clr, t_map *map);

void	txr_cpy(char c, char *line, int len, t_txr *txr);
int		txr_malloc(char c, int len, t_txr *txr);
int		txr_parse(char c, char *line, t_txr *txr);

int		res_parse(char *line, t_res *res);
int		map_parse(int fd, char *line, t_map *map);
int		parse(int fd, t_res *res, t_txr *txr, t_clr *clr, t_map *map);

void	clr_rgb(char c, int *rgb, t_clr *clr);
int		clr_atoi(char c, char *line, t_clr *clr);
int		clr_malloc(char c, int len, t_clr *clr);
int		clr_parse(char c, char *line, t_clr *clr);

#endif