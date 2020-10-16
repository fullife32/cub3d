# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 17:20:04 by eassouli          #+#    #+#              #
#    Updated: 2020/10/16 17:00:28 by eassouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	get_next_line/get_next_line.c\
				get_next_line/get_next_line_utils.c\
				cub3d.c\
				init.c\
				parse.c\
				res_parse.c\
				txr_parse.c\
				clr_parse.c\
				map_parse.c\
				map_leak.c\
				flood_fill.c\
				stack.c\
				raycast.c\
				raycast2.c\
				display.c\
				walls.c\
				spr_cfg.c\
				spr_sort.c\
				keys.c\
				music.c

LIBS		=	srcs/libft/libft.a\
				libmlx.a

PATH		=	srcs/

OBJS		=	$(addprefix $(PATH), $(SRCS))

NAME		=	cub3D

CC			=	/usr/bin/clang

HEADER		=	headers

FLAGS		=	-g -Wall -Wextra -Werror -I $(HEADER) -L/usr/include/../lib -lXext -lX11 -lm -lbsd

RM			=	/bin/rm -f

MAKE		=	/usr/bin/make

LIBFT		=	srcs/libft

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
