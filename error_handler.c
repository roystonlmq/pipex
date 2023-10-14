/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:10:55 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 14:15:40 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_putstr_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}

void	exception(char *error)
{
	perror(error);
	exit(1);
}
