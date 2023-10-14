/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:30:43 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 12:48:14 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h> // fork
# include <sys/wait.h> // wait, waitpid
# include <string.h> // strerror
# include <fcntl.h> // open, unlink
# include <stdio.h> // perror
# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // read, write, close, access, dup, dup2, execve, pipe
# include "../GNL/get_next_line.h" // gnl func

# define INFILE "Infile"
# define OUTFILE "Outfile"
# define PIPE "Pipe"
# define ARGS_ERR "Num of args should be 5"
# define CMD_ERR "Invalid cmd\n"

/* 
Argument index for infd, outfd
./pipex file1 cmd1 cmd2 file2
0		1	  2	   3    4
*/
# define INFD 1
# define OUTFD 4


typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		infd;
	int		outfd;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
}	t_pipe;


#endif
