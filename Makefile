# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tessa <tessa@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/21 11:24:39 by tessa         #+#    #+#                  #
#    Updated: 2022/02/03 17:59:29 by tessa         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	philosophers

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

LDFLAGS		=	-pthread -g -fsanitize=thread

SRCS_DIR	=	srcs/

SRCS		=	check_input.c		\
				eat_sleep_think.c	\
				main.c				\
				mutexes.c			\
				parser.c			\
				setup_simulation.c	\
				start_simulation.c	\
				utils_mutexes.c		\
				utils_parser.c		\
				utils.c

OBJS_DIR	=	objs/

OBJS		=	$(SRCS:%.c=$(OBJS_DIR)%.o)

HEADERFILES	=	./includes/philosophers.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERFILES)
	@mkdir -p $(OBJS_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
