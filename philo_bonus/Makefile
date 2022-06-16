# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/09 13:56:29 by lelhlami          #+#    #+#              #
#    Updated: 2022/04/26 17:43:39 by lelhlami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC_PATH  = srcs_bonus

OBJ_PATH  = objs_bonus

SOURCES = 	philo_bonus.c \
			utils_bonus.c \
			utils2_bonus.c \
			utils3_bonus.c

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))

OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

HEADER = philo_bonus.h

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
	@echo "$(GREEN)Bonus part successfully compiled"
	
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c include_bonus/$(HEADER)
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating bonus object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

tmp:
	@mkdir -p objs_bonus

%.o : %.c
	@$(CC) $(FLAGS) -c $<

clean:
	@echo "$(VIOLET)Deleting Bonus Philosophers object library files$(CYAN)"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re: fclean all

.PHONY: tmp, re, fclean, clean, all