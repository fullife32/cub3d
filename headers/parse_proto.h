/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_proto.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 15:16:14 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/19 19:00:43 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_PROTO_H
#define PARSE_PROTO_H

void	error(int error, t_a *a);

void	txr_init(t_a *a);
void	init(t_a *a);

void	cub_check(char *av, t_a *a);
void	save_check(char *av, t_a *a);

void	parse(t_a *a);

void	res_parse(t_a *a);

int		dup_check(char c);
void	txr_cpy(char c, char *line, int len, t_txr *txr);
int		txr_malloc(char c, int len, t_txr *txr);
void	txr_parse(char c, char *line, t_a *a);

int		txr_atoi(char c, char *line, t_txr *txr);

int		add_line(char *line, t_list	**first, t_list	**lst);
int		start_p(int y, char *line, t_plr *plr, t_dir *dir);
void	map_create(t_a *a);
void	map_parse(t_a *a);

int		floodfill_map(char *line, int i, char trg, char rep);

void	play_music(t_a *a);

void	sprite_init(t_a *a);
void	sprite_set(t_a *a);
void	sprite_count(t_a *a);
void	sprite_pos(t_a *a);
void	sprite_list(t_a *a);

void	line_free(t_a *a);
void	parse_free(t_a *a);
void	map_free(char **map);

#endif