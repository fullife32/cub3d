/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:07:34 by eassouli          #+#    #+#             */
/*   Updated: 2020/09/25 15:07:35 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		play_music(const char *music_name)
{
	char	*command;

	if (!(command = ft_strjoin("aplay ", music_name)))
		return (ERR);
	else
	{
		command = ft_strjoin(command, " &");
		system(command);
		free(command);
		return (OK);
	}
}
