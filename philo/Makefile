# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 11:12:24 by yismaili          #+#    #+#              #
#    Updated: 2022/06/01 14:01:48 by yismaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
NAME = philo
FLAGS= -Wall -Wextra -Werror
SRCS = main.c\
		philo.c\
		utiles.c

OBJS=$(SRCS:.c=.o)
INCL= philosophers.h

BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPurple=\033[1;38;5;205m
BRed=\033[1;31m

all:$(NAME)

		@echo "$(BRed)"
		@echo "██████╗░██╗░░██╗██╗██╗░░░░░░█████╗░"
		@echo "██╔══██╗██║░░██║██║██║░░░░░██╔══██╗"
		@echo "██████╔╝███████║██║██║░░░░░██║░░██║"
		@echo "██╔═══╝░██╔══██║██║██║░░░░░██║░░██║"
		@echo "██║░░░░░██║░░██║██║███████╗╚█████╔╝ BY younes ismaili"
		@echo "╚═╝░░░░░╚═╝░░╚═╝╚═╝╚══════╝░╚════╝░"

%.o: %.c $(INCL)
	@echo "$(BPurple) Compile $(BYellow) $^ $(BGreen)to $@"
	$(CC) $(FLAGS) $< $(INCL) -c

$(NAME):$(OBJS)
	@echo "$(BYellow) Make $(BGreen) $@"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@echo "$(BBlue) Clean"
	rm -rf *.o

fclean:clean
	@echo "$(BGreen) Fclean"
	rm -rf *.a
	rm -rf philo
re : fclean all

.PHONY: all clean fclean re