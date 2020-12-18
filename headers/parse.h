/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 17:14:35 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:31:46 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

# define CUB ".cub"
# define SAVE "--save"

typedef struct	s_res
{
	int		w;
	int		h;
}				t_res;

typedef struct	s_txr
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	char	*floor;
	char	*ceiling;
	int		f_rgb;
	int		c_rgb;
}				t_txr;

typedef struct	s_map
{
	char	**map;
	char	**m_cp;
	int		y;
	int		x;
	int		hit;
	int		side;
	t_list	*first;
	t_list	*lst;
}				t_map;

typedef struct	s_plr
{
	double	pos_x;
	double	pos_y;
	double	move_spd;
	double	rot_spd;
}				t_plr;

#endif
