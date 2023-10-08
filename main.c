/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:13:24 by roylee            #+#    #+#             */
/*   Updated: 2023/10/08 17:44:24 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
fd[0] -> reading
fd[1] -> writing
*/
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	childpid;

	pipe(fd);
	childpid = fork();
	(void)	childpid;	
	(void)	argv;
	(void)	envp;
	if (argc != 5)
	{
		ft_putstr_fd("Incorrect num of args\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit(1);
	}
		
}
