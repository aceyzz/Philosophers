# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 09:14:22 by cedmulle          #+#    #+#              #
#    Updated: 2023/12/10 11:44:41 by cedmulle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                  Couleurs                                    #
# ---------------------------------------------------------------------------- #
RST		= \033[0m
R		= \033[1;31m
G		= \033[1;32m
Y		= \033[1;33m
B		= \033[1;34m
M		= \033[1;35m
C		= \033[1;36m
W		= \033[1;37m
# ---------------------------------------------------------------------------- #
#                                 Variables                                    #
# ---------------------------------------------------------------------------- #
NAME	= philo
SRCS	= dinner.c get_set.c init.c main.c monitor.c parse.c safer.c \
			utils_sync.c utils.c write.c
ODIR	= objs/
OBJS	= $(addprefix $(ODIR), $(SRCS:.c=.o))
CC		= gcc
CF		= -Wall -Werror -Wextra -fsanitize=thread -g3
RM		= rm -rf
# ---------------------------------------------------------------------------- #
#                                 Fonctions                                    #
# ---------------------------------------------------------------------------- #
all:		$(ODIR) $(NAME)

$(ODIR):
			@echo "$(C)Object files created: $(ODIR)\t√$(RST)"
			@mkdir -p $(ODIR)

$(ODIR)%.o:	%.c
			@$(CC) $(CF) -c $< -o $@

$(NAME):	$(OBJS)
			@echo "$(C)Executable is created: $(NAME)\t√$(RST)"
			@$(CC) $(CF) $^ -o $@
			@echo "$(G)\nx-----------------------------------------------x$(RST)"
			@echo "$(G)|                                               |$(RST)"
			@echo "$(G)|\t┌─┐┬ ┬┬┬  ┌─┐┌─┐┌─┐┌─┐┬ ┬┌─┐┬─┐┌─┐\t|$(RST)"
			@echo "$(G)|\t├─┘├─┤││  │ │└─┐│ │├─┘├─┤├┤ ├┬┘└─┐\t|$(RST)"
			@echo "$(G)|\t┴  ┴ ┴┴┴─┘└─┘└─┘└─┘┴  ┴ ┴└─┘┴└─└─┘\t|$(RST)"
			@echo "$(G)|                                               |$(RST)"
			@echo "$(G)x--------------------------------- by cedmulle -x\n$(RST)"
			@echo "$(Y)Usage : ./$(NAME) <nb_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [nbr_of_meals]\n$(RST)"
			@echo "\033[33mnb_of_philos:\tnumbers of philosophers and forks.$(RST)"
			@echo "\033[33mtime_to_die:\tin milliseconds.$(RST)"
			@echo "\033[33mtime_to_eat:\tin milliseconds.$(RST)"
			@echo "\033[33mtime_to_sleep:\tin milliseconds.$(RST)"
			@echo "\033[33mnb_of_meals:\toptionnal\n$(RST)"

clean:
			@echo "$(M)Object files deleted \t\t√$(RST)"
			@$(RM) $(ODIR)

fclean:		clean
			@echo "$(M)Executable deleted \t\t√$(RST)"
			@$(RM) $(NAME)

re:			fclean all

.PHONY : clean fclean re all

# ---------------------------------------------------------------------------- #
#                          Fonctions supplémentaires                           #
# ---------------------------------------------------------------------------- #
norm:
			@echo "$(Y)Checking the norminette...$(RST)"
			@python3 -m norminette -R CheckDefine

leaks:		re
			@echo "$(Y)\nChecking for memory leaks...$(RST)"
			leaks --atExit -- ./$(NAME) 5 800 200 200 5

race:		re
			@echo "$(Y)\nChecking for race conditions with valgrind...$(RST)"
			valgrind --tool=helgrind ./$(NAME) 5 800 200 200 5
