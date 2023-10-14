/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:30:43 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 11:33:16 by roylee           ###   ########.fr       */
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


typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		in_f;
	int		out_f;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
}


#endif
