# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 15:08:23 by minkim3           #+#    #+#              #
#    Updated: 2023/05/15 15:10:33 by minkim3          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MANDATORY		= mandatory
BONUS      	    = bonus
RM              = rm -f
CP				= cp -f
M_NAME			= philo
B_NAME			= philo_bonus
EXEC			= $(MANDATORY)/$(M_NAME)
EXEC_BONUS		= $(BONUS)/$(B_NAME)

all: 
	@make -C $(MANDATORY)
	@$(RM) $(M_NAME)
	@$(CP) $(MANDATORY)/$(M_NAME) $(M_NAME)

bonus:
	@make -C $(BONUS)
	@$(CP) $(BONUS)/$(B_NAME) $(B_NAME)

clean:
	@make clean -C $(MANDATORY)
	@make clean -C $(BONUS)

fclean: clean
	@$(RM) $(M_NAME) $(B_NAME)
	@make fclean -C $(MANDATORY)
	@make fclean -C $(BONUS)

re:
	@make fclean
	@make all

norm:
	norminette -R CheckDefine

.PHONY: all bonus clean fclean re norm

RED = \033[1;31m
PINK = \033[1;35m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
DEFAULT = \033[0m