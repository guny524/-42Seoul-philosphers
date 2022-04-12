# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 20:44:47 by min-jo            #+#    #+#              #
#    Updated: 2022/04/12 20:44:49 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	program_name
BNAME		=	bonus_name

SRC_DIR		=	src/
SRC_ORI		=	source1.c\
				source2.c
BSRC_ORI	=	source1_bonus.c\
				source2_bonus.c

HD_DIR		=	include/

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_ORI))
BSRCS		=	$(addprefix $(SRC_DIR), $(BSRC_ORI))

OBJS		=	$(SRCS:.c=.o)
BOBJS		=	$(BSRCS:.c=.o)

CFLAGS		+=	-Wall -Wextra -Werror -MD
CPPFLAGS	+=	-I $(HD_DIR)
# LDFALGS		+=	-lm

all:		$(NAME)

%.o:		%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

bonus:		$(BOBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $(BNAME)
	touch bonus

clean:
	rm -f $(OBJS) $(BOBJS)
	rm -f $(OBJS:.o=.d)
	rm -f $(BOBJS:.o=.d)
	rm -f bonus

fclean:		clean
	rm -f $(NAME) $(BNAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(OBJS:.o=.d)
-include $(BOBJS:.o=.d)
