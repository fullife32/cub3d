/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 17:14:35 by eassouli          #+#    #+#             */
/*   Updated: 2020/03/31 17:52:13 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "get_next_line/get_next_line.h"

#define ERR -1
#define SPACE 3
#define NO 4
#define SO 5
#define WE 6
#define EA 7

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

int	parse(int fd, t_res *res, t_txr *txr, t_clr *clr);

#endif