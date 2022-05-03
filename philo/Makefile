# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 20:44:47 by min-jo            #+#    #+#              #
#    Updated: 2022/05/07 16:08:27 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRC_DIR		=	src/
SRC_ORI		=	main.c parse.c run.c philo.c philo_state.c ft_time.c ft_str.c\
				ft_err.c ft_err2.c

HD_DIR		=	include/

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_ORI))

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-Wall -Wextra -Werror -MD -g -fsanitize=address
CPPFLAGS	+=	-I $(HD_DIR)
LDFALGS		+=	-lpthread

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

re:
	make fclean
	make all

.PHONY:		all clean fclean re

-include $(OBJS:.o=.d)
