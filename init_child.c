/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:56:24 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 12:39:43 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*cmd(char **path_args, char *name)
{
	char	*ret_cmd;
	char	*tmp;

	while (*path_args)
	{
		tmp = ft_strjoin(*paths, "/");
		ret_cmd = ft_strjoin(tmp, name);
		free(tmp);
		if (access(command, F_OK) == F_OK)
			return (ret_cmd);
		free(ret_cmd);
		path_args++;
	}
	return (0);
}

/*
exec_child2: Responsible for reading from pipe

Duplicate the read end of the pipe to STDIN & closes write end of the pipe
Write end is not used, so it is closed. 
*/
void	child_reader(t_pipe piper, char **argv, char **envp)
{
	dup2(piper.pipe[0], 0);
	close(piper.pipe[1]);
	dup2(piper.outfd, 1);
	piper.cmd_args = ft_split(argv[3], ' ');
	piper.cmd = cmd(piper.cmd_paths, piper.cmd_args[0]);
	if (!piper.cmd)
	{
		free_child(&piper);
		err_msg(CMD_ERR);
		exit(1);
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
	dup2(piper.pipe[1], 1);
	close(piper.pipe[0]);
	dup2(piper.infd, 0);
	piper.cmd_args = ft_split(argv[2], ' ');
	piper.cmd = cmd(piper.cmd_paths, piper.cmd_args[0]);
	if (!piper.cmd)
	{
		free_child(&piper);
		err_msg(CMD_ERR);
		exit(1);
	}
	execve(piper.cmd, piper.cmd_args, envp);
}
