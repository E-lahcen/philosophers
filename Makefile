# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/09 13:56:29 by lelhlami          #+#    #+#              #
#    Updated: 2022/05/18 11:19:00 by lelhlami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_PATH  = srcs

OBJ_PATH  = objs

SOURCES = 	philo.c \
			utils.c \
			utils3.c \
			utils2.c \
			check_data.c

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))

OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

HEADER = philo.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

all: tmp $(NAME) 

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $@ 
	@echo "$(GREEN)Project successfully compiled"
	
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c include/$(HEADER)
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

tmp:
	@mkdir -p objs

%.o : %.c
	@$(CC) $(FLAGS) -c $<

clean:
	@echo "$(VIOLET)Deleting Philosophers library files$(CYAN)"
	@rm -f $(OBJS)
	@make clean -C ../philo_bonus

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@make fclean -C ../philo_bonus

re: fclean all

bonus:
	make -C ../philo_bonus
.PHONY: tmp, re, fclean, clean, bonus, all
