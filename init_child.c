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

/*
child_reader: Responsible for reading from pipe

Duplicate the read end of the pipe to STDIN & closes write end of the pipe
Write end is not used, so it is closed. 
*/
void	child_reader(t_pipe piper, char **argv, char **envp)
{
	dup2(piper.pipe[READ], STDIN_FILENO);
	close(piper.pipe[READ]);
	close(piper.pipe[WRITE]);
	dup2(piper.outfd, STDOUT_FILENO);
	piper.cmd_args = ft_split(argv[3], ' ');
	piper.cmd = cmd(piper.cmd_paths, piper.cmd_args[0]);
	if (!piper.cmd)
	{
		close_child(&piper);
		exception(CMD_ERR);
	}
	execve(piper.cmd, piper.cmd_args, envp);
}

/*
child_writer: Responsible for writing from pipe

Duplicate the write end of the pipe to STDOUT & closes read end of the pipe
Read end is not used so it is closed.
Ensures any attempt to read from the pipe will result in EOF condition
*/
void	child_writer(t_pipe piper, char **argv, char **envp)
{
	dup2(piper.pipe[WRITE], STDOUT_FILENO);
	close(piper.pipe[WRITE]);
	close(piper.pipe[READ]);
	dup2(piper.infd, STDIN_FILENO);
	piper.cmd_args = ft_split(argv[2], ' ');
	piper.cmd = cmd(piper.cmd_paths, piper.cmd_args[0]);
	if (!piper.cmd)
	{
		close_child(&piper);
		exception(CMD_ERR);
	}
	execve(piper.cmd, piper.cmd_args, envp);
}
