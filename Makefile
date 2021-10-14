# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iltafah <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 17:10:00 by iltafah           #+#    #+#              #
#    Updated: 2021/10/14 15:50:17 by iltafah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC := gcc

CFLAGS := -Wall -Wextra -Werror

MAND_SRC := philo/philosopher_main.c

# BONS_SRC :=

OBJ_DIR := obj

MAND_OBJ := $(addprefix $(OBJ_DIR)/, $(MAND_SRC:%.c=%.o))

# BONS_SRC := $(addprefix $(OBJ_DIR), $(BONS_SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(MAND_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(MAND_OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
