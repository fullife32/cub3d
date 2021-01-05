# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 17:20:04 by eassouli          #+#    #+#              #
#    Updated: 2021/01/02 16:01:44 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

PATH		=	srcs/

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
				parse/map_parse.c\
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

OBJS		=	$(addprefix $(PATH), $(SRCS))

LIBFT		=	srcs/libft

MAKE		=	/usr/bin/make

CC			=	/usr/bin/clang

LIBS		=	srcs/libft/libft.a\
				minilibx_linux/libmlx.a

HEADER		=	headers

SAVE		=	save.bmp

FLAGS		=	-g -Wall -Wextra -Werror -I $(HEADER) -L/usr/include/../lib -lXext -lX11 -lm -lbsd

RM			=	/bin/rm -f

all:		$(NAME) #attention a la recompilation

$(NAME):	$(OBJS)
			$(MAKE) -s -C $(LIBFT)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS) $(LIBS)

clean:
			$(MAKE) -s -C $(LIBFT) clean
			$(RM) $(SAVE)

fclean:		clean
			$(RM) $(NAME)
			$(RM) srcs/libft/libft.a

re:			fclean all

.PHONY:		all clean fclean re
