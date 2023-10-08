# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roylee <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/08 13:53:53 by roylee            #+#    #+#              #
#    Updated: 2023/10/08 14:13:05 by roylee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c

OBJS = $(SRCS:.c=.o)

NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

INC = -I libft/

ADDLIB = -L libft -l ft

LIBFT = libft/libft.a

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): 
	@make -C libft

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(ADDLIB) -o $(NAME) 

clean:
	@make -C libft clean
	@$(RM) $(OBJS)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)

re: fclean all

norm: 
	norminette 

.PHONY: all re fclean clean
