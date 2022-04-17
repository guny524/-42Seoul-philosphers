# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 20:44:47 by min-jo            #+#    #+#              #
#    Updated: 2022/04/16 16:14:32 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus

SRC_DIR		=	src/
SRC_ORI		=	source1.c\
				source2.c

HD_DIR		=	include/

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_ORI))

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-Wall -Wextra -Werror -MD
CPPFLAGS	+=	-I $(HD_DIR)
# LDFALGS		+=	-lm

all:		$(NAME)

%.o:		%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS:.o=.d)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(OBJS:.o=.d)
