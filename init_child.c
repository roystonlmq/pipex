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
execute_args: Executes shell command with its args

Uses space as a delimiter to find the args. 
Known bug: Does not work with diff quotes
*/
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
			CHILD 1		  	  PIPE			 CHILD 2	 
INFILE (IN) ls -l  (OUT) (IN) ---- (OUT)(IN) wc -l (OUT) OUTFILE

execute_child: Executes the child process based on cmd_idx

If CMD1, write end of the pipe is duplicated to STDOUT and IN FD is duplicated
to STDIN. Executes CMD1 such that the output is written into the pipe.

If CMD2, read end of the pipe is duplicated to STDIN and OUT FD is duplicated
to STDOUT. Executes CMD2 such that the input from the pipe is absorbed and 
outputs the result in STDOUT.
*/
void	execute_child(t_pipe piper, char **argv, char **envp, int cmd_idx)
{
	if (cmd_idx == CMD1)
	{
		dup2(piper.infd, STDIN_FILENO);
		dup2(piper.pipe[WRITE], STDOUT_FILENO);
		close_pipe(&piper);
		execute_args(piper, argv, envp, cmd_idx);
	}
	else
	{
		dup2(piper.outfd, STDOUT_FILENO);
		dup2(piper.pipe[READ], STDIN_FILENO);
		close_pipe(&piper);
		execute_args(piper, argv, envp, cmd_idx);
	}
}
