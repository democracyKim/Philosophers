# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 13:20:47 by minkim3           #+#    #+#              #
#    Updated: 2023/05/14 17:37:01 by minkim3          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -MMD
NAME            = philo
RM              = rm -f

EXEC            = philo
SRCS_PATH	    = ./mandatory/

MAIN_PATH  	    = ./main/
MAIN_SRCS       = main.c
MAIN            = $(addprefix $(MAIN_PATH), $(MAIN_SRCS))

INIT_PATH  	    = ./init/
INIT_SRCS       = init.c get_info.c
INIT            = $(addprefix $(INIT_PATH), $(INIT_SRCS))

UTILS_PATH      = ./utils/
UTILS_SRCS      = ft_atoi.c ft_calloc.c ft_strcmp.c get_time.c
UTILS           = $(addprefix $(UTILS_PATH), $(UTILS_SRCS))

PHILO_PATH      = ./philo/
PHILO_SRCS      = life_of_philo.c start_threads.c monitoring.c \
				  fin_philo.c eating.c print_state.c
PHILO           = $(addprefix $(PHILO_PATH), $(PHILO_SRCS))

SOURCES			= $(addprefix $(SRCS_PATH), $(MAIN))\
				  $(addprefix $(SRCS_PATH), $(INIT))\
				  $(addprefix $(SRCS_PATH), $(UTILS))\
				  $(addprefix $(SRCS_PATH), $(PHILO))

OBJECTS         = $(SOURCES:.c=.o)

HEADER_PATH     = ./includes/
S_HEADER        = philo.h
HEADER          = $(addprefix $(HEADER_PATH), $(S_HEADER))

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)
	@echo -e "$(GREEN)$(EXEC) created!$(DEFAULT)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus:
	@make -C $(BONUS)
	@$(CP) $(BONUS)/$(NAME) $(NAME)
	@echo -e "$(BLUE)bonus compiled!$(DEFAULT)"

clean:
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS:.o=.d)
	@echo -e "$(PINK)delete object files!$(DEFAULT)"

fclean: clean
	@$(RM) $(EXEC)
	@echo -e "$(YELLOW)delete all!$(DEFAULT)"

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