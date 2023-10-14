/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:30:43 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 14:12:13 by roylee           ###   ########.fr       */
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

# define INFILE "Infile"
# define OUTFILE "Outfile"
# define PIPE "Pipe"
# define ENV_ERR "Invalid environment"
# define ARGS_ERR "Num of args should be 5"
# define CMD_ERR "Invalid cmd\n"

/* 
Argument index for infd, outfd
./pipex file1 cmd1 cmd2 file2
0		1	  2	   3    4
*/
# define INFD 1
# define OUTFD 4

/*
CONSTS to define read and write end of pipe
*/
# define READ 0
# define WRITE 1

typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		infd;
	int		outfd;
	char	*envpaths;
	char	**cmd_paths;
	char	**cmd_args;
}	t_pipe;

/*
cleaner.c
*/
void	close_all(t_pipe *piper);
void	close_parent(t_pipe *piper);
void	close_child(t_pipe *piper);

/*
error_handler.c
*/
int		putstr_fd(int fd, char *s);
void	exception(char *error);

/*
init_child.c
*/
void	child_reader(t_pipe piper, char **argv, char **envp);
void	child_writer(t_pipe piper, char **argv, char **envp);

/*
mem.c
*/
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);

/*
string.c
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);

/*
ft_split.c
*/
char	**ft_split(const char *s, char c);
#endif
