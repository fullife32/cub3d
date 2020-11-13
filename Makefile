# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 17:20:04 by eassouli          #+#    #+#              #
#    Updated: 2020/11/13 17:16:35 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

PATH		=	srcs/

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
				bitmap.c\
				errors.c\
				args_check.c

OBJS		=	$(addprefix $(PATH), $(SRCS))

LIBFT		=	srcs/libft

MAKE		=	/usr/bin/make

CC			=	/usr/bin/clang

LIBS		=	srcs/libft/libft.a\
				minilibx_linux/libmlx.a

HEADER		=	headers

FLAGS		=	-g -Wall -Wextra -Werror -I $(HEADER) -L/usr/include/../lib -lXext -lX11 -lm -lbsd

RM			=	/bin/rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			@cd $(LIBFT) && $(MAKE) re && $(MAKE) clean
			$(CC) -o $(NAME) $(FLAGS) $(OBJS) $(LIBS)

clean:
			$(RM) srcs/libft/libft.a

fclean:		clean
			$(RM) $(NAME) #add bmp delete

re:			fclean all

.PHONY:		all clean fclean re
