/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:30:43 by roylee            #+#    #+#             */
/*   Updated: 2023/11/04 19:10:41 by roylee           ###   ########.fr       */
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
# define CMD1 2
# define CMD2 3
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
	char	*cmd;
}	t_pipe;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_cmds
{
	t_list	*cmd_list;
	t_list	*head;
	char	*param;
	size_t	cmdidx;
	size_t	ch_parsed;
	size_t	cmdlen;
}	t_cmds;

typedef struct s_quote
{
	int	j;
	int	k;
	int	quote_type;
}	t_quote;

/*
cleaner.c
*/
void	close_pipe(t_pipe *piper);
void	close_parent(t_pipe *piper);
void	close_child(t_pipe *piper);

/*
error_handler.c
*/
int		ft_putstr_fd(int fd, char *s);
void	exception(char *error);

/*
init_child.c
*/
void	execute_child(t_pipe piper, char **argv, char **envp, int cmd_idx);

/*
mem.c
*/
void	*ft_memcpy(void *dest, const void *src, size_t n);

/*
string.c
*/
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/*
string2.c
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);

/*
ft_split.c
*/
char	**ft_split(const char *s, char c);

/* 
list.c
*/
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
char	**lst_to_strarr(t_list *lst);

/*
cmd_split.c
*/
t_list	*cmd_split(const char *cmdstr);
#endif
