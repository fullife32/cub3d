# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 17:20:04 by eassouli          #+#    #+#              #
#    Updated: 2020/11/03 15:57:14 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	get_next_line/get_next_line.c\
				get_next_line/get_next_line_utils.c\
				parse/parse_color.c\
				parse/parse_map.c\
				parse/parse_resolution.c\
				parse/parse_texture.c\
				parse/parse.c\
				sprite/sprite_list.c\
				sprite/sprite_dist.c\
				cub3d.c\
				init.c\
				map_leak.c\
				flood_fill.c\
				stack.c\
				raycast.c\
				raycast_wall.c\
				raycast_sprite.c\
				display.c\
				walls.c\
				keys_move.c\
				keys_bind.c\
				music.c\
				bitmap.c

LIBS		=	srcs/libft/libft.a\
				minilib_linux/libmlx.a

PATH		=	srcs/

OBJS		=	$(addprefix $(PATH), $(SRCS))

NAME		=	cub3D

CC			=	/usr/bin/clang

HEADER		=	headers

FLAGS		=	-g -Wall -Wextra -Werror -I $(HEADER) -L/usr/include/../lib -lXext -lX11 -lm -lbsd

RM			=	/bin/rm -f

MAKE		=	/usr/bin/make

LIBFT		=	srcs/libft

LIBMLX		=	minilibx_linux

all:		$(NAME)

$(NAME):	$(OBJS)
			@cd $(LIBFT) && $(MAKE) re && $(MAKE) clean
			$(CC) -o $(NAME) $(FLAGS) $(OBJS) $(LIBS)

%.o:		%.c
			$(CC) $(FLAGS) -o $@
	
clean:
			$(RM) srcs/libft/libft.a

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
