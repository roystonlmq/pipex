/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:13:24 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 14:12:53 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Takes envp args ('\0' terminated) which are of form key=value
Once "PATH" is found, pointer is moved to the first char of the path
Note: format of PATH is "PATH=[path]"
*/
static char	*get_envpath(char **envp)
{
	if (!envp)
		return (0);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

/*
fd[0] -> read end of pipe
fd[1] -> write end of pipe
The parent process is cloned twice (pid1 and pid2)
Each instance of the clone (pid1/pid2) will be used for 
executing the write and read end of the pipe
*/
int	main(int argc, char **argv, char **envp)
{
	t_pipe	piper;

	if (argc != 5)
		return (ft_putstr_fd(2, ARGS_ERR));
	piper.infd = open(argv[INFD], O_RDONLY);
	if (piper.infd < 0)
		exception(INFILE);
	piper.outfd = open(argv[OUTFD], O_CREAT | O_RDWR | O_TRUNC);
	if (piper.outfd < 0)
		exception(OUTFILE);
	piper.envpaths = get_envpath(envp);
	if (piper.envpaths == 0)
		exception(ENV_ERR);
	piper.cmd_paths = ft_split(piper.envpath, ':');
	piper.pid1 = fork();
	if (piper.pid1 == 0)
		child_reader(piper, argv, envp);
	piper.pid2 = fork();
	if (piper.pid2 == 0)
		child_writer(piper, argv, envp);
	close_all(&piper);
	waitpid(piper.pid1, NULL, 0);
	waitpid(piper.pid2, NULL, 0);
	close_parent(&piper);
}
