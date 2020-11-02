# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    music.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 14:59:10 by eassouli          #+#    #+#              #
#    Updated: 2020/11/02 17:08:53 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

while pidof ./cub3D > /dev/null == true ; do
	ret = aplay --quiet ./sounds/bfg10k.wav ;
	if [ ret != 1 ] ; do
		break
	done
done
