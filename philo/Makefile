# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 09:14:22 by cedmulle          #+#    #+#              #
#    Updated: 2023/12/03 13:16:18 by cedmulle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                 Variables                                    #
# ---------------------------------------------------------------------------- #
NAME	= philo
SRCS	= dinner.c get_set.c init.c main.c monitor.c parse.c safer.c \
			utils_sync.c utils.c write.c
ODIR	= objs/
OBJS	= $(addprefix $(ODIR), $(SRCS:.c=.o))
CC		= gcc
CF		= -Wall -Werror -Wextra
RM		= rm -rf
# ---------------------------------------------------------------------------- #
#                                 Fonctions                                    #
# ---------------------------------------------------------------------------- #
all:		$(ODIR) $(NAME)

$(ODIR):
			@echo "\033[1;36mObject files created in $(ODIR)\t√\033[0m"
			@mkdir -p $(ODIR)

$(ODIR)%.o:	%.c
			@$(CC) $(CF) -c $< -o $@

$(NAME):	$(OBJS)
			@echo "\033[1;36m$(NAME) executable is created\t√\033[0m"
			@$(CC) $(CF) $^ -o $@
			@echo "\033[1;32m\n ----------------------------------------------- \033[0m"
			@echo "\033[1;32m|\t┌─┐┬ ┬┬┬  ┌─┐┌─┐┌─┐┌─┐┬ ┬┌─┐┬─┐┌─┐\t|\033[0m"
			@echo "\033[1;32m|\t├─┘├─┤││  │ │└─┐│ │├─┘├─┤├┤ ├┬┘└─┐\t|\033[0m"
			@echo "\033[1;32m|\t┴  ┴ ┴┴┴─┘└─┘└─┘└─┘┴  ┴ ┴└─┘┴└─└─┘\t|\033[0m"
			@echo "\033[1;32m|                                               |\033[0m"
			@echo "\033[1;32m --------------------------------- by cedmulle - \n\033[0m"

clean:
			@echo "\033[1;35mObject files deleted \t\t√\033[0m"
			@$(RM) $(ODIR)

fclean:		clean
			@echo "\033[1;35mExecutable deleted \t\t√\033[0m"
			@$(RM) $(NAME)

re:			fclean all

leaks:		re
			@echo "\033[1;33m\nChecking for memory leaks...\033[0m"
			leaks --atExit -- ./$(NAME) 5 800 200 200 5

race:		re
			@echo "\033[1;33m\nChecking for race conditions with valgrind...\033[0m"
			valgrind --tool=helgrind ./$(NAME) 5 800 200 200 5

.PHONY : clean fclean re all
