# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    music.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 14:59:10 by eassouli          #+#    #+#              #
#    Updated: 2020/12/23 17:31:15 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

while pidof ./cub3D > /dev/null == true ; do
	aplay --quiet ./sounds/spoiler.wav
done
