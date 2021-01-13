# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 17:20:04 by eassouli          #+#    #+#              #
#    Updated: 2021/01/13 19:08:48 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

CC	=	/usr/bin/clang

CFLAGS	=	 -g -Wall -Wextra -Werror $(INCLUDES)

DFLAGS	=	-L/usr/lib -lXext -lX11 -lm -lbsd \
	-Llibft -lft \
	-L$(LIBS)minilibx_linux -lmlx

MAKE	=	/usr/bin/make -s -C

RM	=	/bin/rm -rf

LIBS	=	libs/

LIBFT	=	libft

PATH	=	srcs/

SAVE	=	save.bmp

INCLUDES	=	-I headers \
	-I $(PATH)get_next_line \
	-I $(LIBFT) \
	-I $(LIBS)minilibx_linux

SRCS	+=	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c

SRCS	+=	cub3d.c

SRCS	+=	destroy/errors.c\
	destroy/free_parse.c\
	destroy/free_raycast.c

SRCS	+=	parse/args_check.c\
	parse/init_parse.c\
	parse/parse.c\
	parse/resolution_parse.c\
	parse/color_parse.c\
	parse/texture_parse.c\
	parse/texture_malloc.c\
	parse/sprite_list.c\
	parse/map_parse.c\
	parse/map_position.c

SRCS	+=	flood_fill/map_leak.c\
	flood_fill/stack.c\
	flood_fill/flood_fill.c

SRCS	+=	raycast/init_raycast.c\
	raycast/textures_set.c\
	raycast/raycast.c\
	raycast/sprite_dist.c\
	raycast/wall_raycast.c\
	raycast/wall_select.c\
	raycast/sprite_raycast.c\
	raycast/display.c

SRCS	+=	bonus/bitmap.c\
	bonus/music.c

SRCS	+=	events/keys_bind.c\
	events/keys_move.c

OBJS	=	$(addprefix $(PATH), $(SRCS:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJS)
	$(MAKE) $(LIBFT)
	$(CC) $(OBJS) $(DFLAGS) -o $(NAME)

clean:
	$(MAKE) $(LIBFT) clean

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(SAVE)
	$(RM) $(OBJS)
	$(MAKE) $(LIBFT) fclean

re:	fclean all

.PHONY:	all clean fclean re
