# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roylee <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 23:26:11 by roylee            #+#    #+#              #
#    Updated: 2023/09/24 17:19:06 by roylee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = srcs/ft_printf.c
OBJS = $(SRCS:.c=.o)
CC = cc -Wall -Werror -Wextra -c
LIBC = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	mv libft/libft.a $(NAME)
	$(LIBC) $(NAME) $(OBJS)

.c.o:
	$(CC) $< -o $(<:.c=.o)

clean:
	make -C libft clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all 
