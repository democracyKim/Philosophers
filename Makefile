# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 13:20:47 by minkim3           #+#    #+#              #
#    Updated: 2023/04/04 12:29:35 by minkim3          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -MMD -fsanitize=thread
#CFLAGS          = -Wall -Wextra -Werror -MMD -fsanitize=address
NAME            = philo
RM              = rm -f

EXEC            = philo
SRCS_PATH	   = ./mandatory/
SRCS			= main.c\
				  utils/ft_atoi.c\
				  utils/ft_calloc.c\
				  utils/error.c\
				  utils/ft_strcmp.c\
				  init/init.c\
				  init/init_monitoring.c\
				  threads/life_of_philo.c\
				  threads/start_and_close.c\
				  threads/check_status.c\
				  threads/eating.c\
				  threads/print_state.c\
				  threads/time_lapse.c
SOURCES			= $(addprefix $(SRCS_PATH), $(SRCS))
OBJECTS         = $(SOURCES:.c=.o)
S_HEADER  	    = philo.h
HEADER			= $(addprefix $(SRCS_PATH), $(S_HEADER))

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)
	@echo -e "$(GREEN)$(EXEC) created!$(DEFAULT)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:
	@make -C $(BONUS)
	@$(CP) $(BONUS)/$(NAME) $(NAME)
	@echo -e "$(BLUE)copied!$(DEFAULT)"

clean:
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS:.o=.d)

fclean: clean
	@$(RM) $(EXEC)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re

-include $(OBJECTS:.o=.d)

RED = \033[1;31m
PINK = \033[1;35m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
DEFAULT = \033[0m