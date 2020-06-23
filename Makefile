# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 17:20:04 by eassouli          #+#    #+#              #
#    Updated: 2020/06/23 14:43:20 by eassouli         ###   ########.fr        #
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
raycast.c

LIBS		= libft/libft.a\
libmlx.dylib

PATH		= srcs/

OBJS		= $(addprefix $(PATH), $(SRCS:.c=.o))

NAME		= cub3d

CC			= gcc

HEADER		= headers

FLAGS		= -g -Wall -Wextra -Werror -I $(HEADER)

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS) $(LIBS)

%.o:		%.c
			$(CC) $(FLAGS) -o $@ -c $<
	
clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
