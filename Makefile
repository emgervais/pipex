# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egervais <egervais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 14:49:38 by egervais          #+#    #+#              #
#    Updated: 2023/05/26 15:22:24 by egervais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex
CFLAGS	:= -Wextra -Wall  -fsanitize=address -g
SRCS	:= main.c ft_strjoin.c ft_split.c parsing.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re