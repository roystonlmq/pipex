# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roylee <roylee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/08 13:53:53 by roylee            #+#    #+#              #
#    Updated: 2023/10/14 14:10:52 by roylee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c init_child.c ft_split.c mem.c string.c

OBJS = $(SRCS:.c=.o)

NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

INC = -I .

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

norm: 
	norminette 

.PHONY: all re fclean clean
