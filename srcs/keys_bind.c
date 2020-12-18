/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:34:50 by eassouli          #+#    #+#             */
/*   Updated: 2020/12/18 15:30:36 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_a *a)
{
	a->mov.mov[key] = OK;
	return (OK);
}

int		key_release(int key, t_a *a)
{
	a->mov.mov[key] = FALSE;
	return (OK);
}
