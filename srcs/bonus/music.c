/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:07:34 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/07 14:32:33 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_music(t_a *a)
{
	system("sh ./sounds/music.sh & > /dev/null");
	a->bmp.fd = -2;
}
