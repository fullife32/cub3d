# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 17:20:04 by eassouli          #+#    #+#              #
#    Updated: 2021/01/11 00:42:07 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

CC			=	/usr/bin/clang

CFLAGS		=	 -g -Wall -Wextra -Werror $(HEADERS)

DFLAGS		=	-L/usr/lib -lXext -lX11 -lm -lbsd \
				-L$(LIBS)libft -lft \
				-L$(LIBS)minilibx_linux -lmlx

MAKE		=	/usr/bin/make -s -C

RM			=	/bin/rm -rf

LIBS		=	libs/

LIBFT		=	$(LIBS)libft

PATH		=	srcs/

SAVE		=	save.bmp

HEADERS		=	-I headers \
				-I $(PATH)get_next_line \
				-I $(LIBS)libft \
				-I $(LIBS)minilibx_linux

SRCS		=	get_next_line/get_next_line.c\
				get_next_line/get_next_line_utils.c\
				cub3d.c\
				args_check.c\
				wall.c\
				parse/init_parse.c\
				parse/free_parse.c\
				parse/parse.c\
				parse/resolution_parse.c\
				parse/color_parse.c\
				parse/texture_parse.c\
				parse/texture_malloc.c\
				parse/map_parse.c\
				parse/map_position.c\
				flood_fill/map_leak.c\
				flood_fill/stack.c\
				flood_fill/flood_fill.c\
				raycast/init_raycast.c\
				raycast/free_raycast.c\
				raycast/textures_set.c\
				raycast/raycast.c\
				raycast/wall_raycast.c\
				raycast/sprite_raycast.c\
				raycast/display.c\
				sprite/sprite_list.c\
				sprite/sprite_dist.c\
				bitmap.c\
				keys_bind.c\
				keys_move.c\
				music.c\
				errors.c

OBJS		=	$(addprefix $(PATH), $(SRCS:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) $(LIBFT)
			$(CC) $(OBJS) $(DFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)
			$(MAKE) $(LIBFT) clean

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(SAVE)
			$(MAKE) $(LIBFT) fclean

re:			fclean all

.PHONY:		all clean fclean re

# depend:		.depend

# .depend:	$(OBJ)
# 			$(RM) ./.depend
# 			$(CC) $(OBJS) $(DFLAGS) $(HEADERS) -MM $^ > ./.depend;

# -include .depend