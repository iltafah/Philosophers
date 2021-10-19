# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iltafah <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 17:10:00 by iltafah           #+#    #+#              #
#    Updated: 2021/10/19 15:35:15 by iltafah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC := gcc

CFLAGS := -Wall -Wextra -Werror

MAND_SRC := philosopher_main.c \
simulation.c            \
death_thread.c           \
print_status.c            \
get_data_struct.c          \
get_curr_time_in_ms.c       \
create_eating_count_thread.c \
create_process_per_philosopher.c

OBJ_DIR := obj

MAND_OBJ := $(addprefix $(OBJ_DIR)/, $(MAND_SRC:%.c=%.o))

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
