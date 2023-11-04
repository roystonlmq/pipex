/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:54:22 by roylee            #+#    #+#             */
/*   Updated: 2023/11/04 19:14:03 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_quote(char c)
{
	if (c == '\'')
		return ((int) '\'');
	if (c == '\"')
		return ((int) '\"');
	return (0);
}

static int	find_cmdidx(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

static void	quote_type_check(t_quote *data)
{
	if (!data->quote_type && is_quote(s[data->j]))
	{
		data->k = data->j + 1;
		quote_type = s[data->j];
	}
}

static int	parse_quote(const char *s, char **param)
{
	t_quote	data;

	data.j = 0;
	data.quote_type = 0;
	while (s[data.j++])
	{
		if (data.quote_type && (s[data.j] == '\\'
				|| s[data.j] == '\"' || s[data.j] == '\''))
		{
			if (s[data.j + 1] && (s[data.j + 1] == '\"'
					|| s[data.j + 1] == '\"'))
				data.j += 2;
			if (data.quote_type && data.quote_type == is_quote(s[data.j]))
			{
				*param = malloc(data.j - data.k + 2);
				if (!*param)
					return (-1);
				ft_strlcpy(*param, s + data.k, data.j - data.k + 1);
				break ;
			}
		}
		quote_type_check(&data);
	}
	return (j);
}

t_list	*cmd_split(const char *cmdstr)
{
	t_cmds	cmdargs;
	int		k;

	cmdargs.cmdidx = find_cmdidx(cmdstr);
	cmdargs.param = NULL;
	cmdargs.cmd_list = ft_lstnew(ft_substr(cmdstr, 0, cmdargs.cmdidx));
	cmdargs.head = cmdargs.cmd_list;
	cmdargs.cmdlen = ft_strlen(cmdstr);
	cmdargs.ch_parsed = 0 + cmdargs.cmdidx;
	while (cmdargs.ch_parsed < cmdargs.cmdlen - 1)
	{
		cmdargs.ch_parsed += parse_quote(cmdstr + \
		cmdargs.ch_parsed, &cmdargs.param, k);
		(cmdargs.cmd_list)->next = ft_lstnew(cmdargs.param);
		cmdargs.cmd_list = (cmdargs.cmd_list)->next;
	}
	cmdargs.cmd_list = cmdargs.head;
	return (cmdargs.cmd_list);
}

/*
static char	*get_envpath(char **envp)
{
	if (!envp)
		return (0);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	*path_to_cmd(char **path_args, char *name)
{
	char	*ret_cmd;
	char	*tmp;

	while (*path_args)
	{
		tmp = ft_strjoin(*path_args, "/");
		ret_cmd = ft_strjoin(tmp, name);
		free(tmp);
		if (access(ret_cmd, 0) == 0)
		{
			printf("the ret cmd is %s \n", ret_cmd);
			return (ret_cmd);
		}
		free(ret_cmd);
		path_args++;
	}
	if (access(name, 0) == 0)
	{
		printf("could not find the cmd, but found the cmd in the cwd. \n");
		return (ret_cmd);
	
	}
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	(void) argc, argv;
 	t_list	*cmd_list;
	t_pipe	piper;
	char	**cmd_strarr;
	const char	*teststr = "awk \"{count++} END {printf \\\"
	count: %i\\\" , count}\" \"/etc/passwd\"";
	// const char	*teststr = "echo \"hello\"";
	cmd_list = cmd_split(teststr);
	cmd_strarr = lst_to_strarr(cmd_list);
	printf("testing cmdstr: %s \n", teststr);

	piper.envpaths = get_envpath(envp);
	if (piper.envpaths == 0)
		exception(ENV_ERR);
	piper.cmd_paths = ft_split(piper.envpaths, ':');
	
	for (int i = 0; cmd_strarr[i]; i++)
	{	
		printf("idx %d : %s \n", i, cmd_strarr[i]);
		// free(cmd_strarr[i]);
	}
	// printf("%s \n", cmd_strarr[3]);
	write(2, "hello \n", ft_strlen("hello \n"));
	
	execve(path_to_cmd(piper.cmd_paths, cmd_strarr[0]), cmd_strarr + 1, NULL);
}
*/