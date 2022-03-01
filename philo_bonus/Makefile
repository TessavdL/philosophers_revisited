# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tessa <tessa@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/21 11:24:39 by tessa         #+#    #+#                  #
#    Updated: 2022/02/28 17:20:25 by tevan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

LDFLAGS		=	-pthread

SRCS_DIR	=	srcs/

SRCS		=	check_input.c				\
				eat_sleep_think.c			\
				main.c						\
				monitoring.c				\
				parser.c					\
				semaphore_initialization.c	\
				semaphore_utils.c			\
				setup_simulation.c			\
				start_simulation.c			\
				time.c						\
				utils.c						\
				utils_itoa.c

OBJS_DIR	=	objs/

OBJS		=	$(SRCS:%.c=$(OBJS_DIR)%.o)

HEADERFILES	=	./includes/philosophers.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) -g -fsanitize=address -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERFILES)
	@mkdir -p $(OBJS_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
