/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:56:24 by roylee            #+#    #+#             */
/*   Updated: 2023/10/15 17:52:09 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Checks whether the sh cmd is a valid file
Returns the full path of the sh cmd
*/
static char	*cmd(char **path_args, char *name)
{
	char	*ret_cmd;
	char	*tmp;

	while (*path_args)
	{
		tmp = ft_strjoin(*path_args, "/");
		ret_cmd = ft_strjoin(tmp, name);
		free(tmp);
		if (access(ret_cmd, 0) == 0)
			return (ret_cmd);
		free(ret_cmd);
		path_args++;
	}
	return (0);
}

void	execute_args(t_pipe piper, char **argv, char **envp, int cmd_idx)
{
	piper.cmd_args = ft_split(argv[cmd_idx], ' ');
	piper.cmd = cmd(piper.cmd_paths, piper.cmd_args[0]);
	if (!piper.cmd)
	{
		close_child(&piper);
		exception(CMD_ERR);
	}
	execve(piper.cmd, piper.cmd_args, envp);
}
/*
Pipe overview

(STDIN) ls -l (OUTFD/WRITE) =======> (INFD/READ) wc -l (STDOUT)

child_reader: Responsible for reading from pipe

Responsible for handling CMD2. Duplicates the read end of the pipe 
to STDIN. 
Write end of the pipe is not used, so it is closed. 
Duplicates the output fd into STDOUT.
*/
void	child_reader(t_pipe piper, char **argv, char **envp, int cmd_idx)
{
	dup2(piper.pipe[READ], STDIN_FILENO);
	close_pipe(piper);
	dup2(piper.outfd, STDOUT_FILENO);
	execute_args(piper, argv, envp, cmd_idx);
}

/*
Pipe overview
t ttesteststsetstsetsttststststststststststststes

(STDIN) ls -l (OUT FD/WRITE) =======> (IN FD/READ) wc -l (STDOUT)

child_writer: Responsible for writing from pipe


Responsible for handling CMD1 because CMD1's output is written to
the pipe (infd)
Duplicate the write end of the pipe to STDOUT.
Read end is not used so it is closed.
Duplicates the input fd into STDIN.

Ensures any attempt to read from the pipe will result in EOF condition
*/
void	child_writer(t_pipe piper, char **argv, char **envp, int cmd_idx)
{
	dup2(piper.pipe[WRITE], STDOUT_FILENO);
	close_pipe(piper);
	dup2(piper.infd, STDIN_FILENO);
	execute_args(piper, argv, envp, cmd_idx);
}
