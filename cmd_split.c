/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:54:22 by roylee            #+#    #+#             */
/*   Updated: 2023/10/29 18:37:30 by roylee           ###   ########.fr       */
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

static int	parse_quote(const char *s, char **param)
{
	int		j;
	int		k;
	int		quote_type;

	quote_type = 0;
	j = 0;
	while (s[j++])
	{
		if (quote_type && quote_type == is_quote(s[j]))
		{
			*param = malloc(j - k + 2);
			if (!*param)
				return (-1);
			ft_strlcpy(*param, s + k, j - k + 1);
			break ;
		}
		if (!quote_type && is_quote(s[j]))
		{
			k = j + 1;
			quote_type = s[j];
		}
	}
	return (j);
}

t_list	*cmd_split(const char *cmdstr)
{
	t_cmds	cmdargs;

	cmdargs.cmdidx = find_cmdidx(cmdstr);
	cmdargs.param = NULL;
	cmdargs.cmd_list = ft_lstnew(ft_substr(cmdstr, 0, cmdargs.cmdidx));
	cmdargs.head = cmdargs.cmd_list;
	cmdargs.cmdlen = ft_strlen(cmdstr);
	cmdargs.ch_parsed = 0 + cmdargs.cmdidx;
	while (cmdargs.ch_parsed < cmdargs.cmdlen - 1)
	{
		cmdargs.ch_parsed += parse_quote(cmdstr + \
		cmdargs.ch_parsed, &cmdargs.param);
		(cmdargs.cmd_list)->next = ft_lstnew(cmdargs.param);
		cmdargs.cmd_list = (cmdargs.cmd_list)->next;
	}
	cmdargs.cmd_list = cmdargs.head;
	return (cmdargs.cmd_list);
}
/*
int	main(void)
{
	t_list	*cmd_list;
	char	**cmd_strarr;
	const char	*teststr = "awk \"{count++} END \
	{printf \"count: %i\" , count}\" \"/etc/passwd\"";
	cmd_list = cmd_split(teststr);
	cmd_strarr = lst_to_strarr(cmd_list);
	printf("testing cmdstr: %s \n", teststr);
	for (int i = 0; cmd_strarr[i]; i++)
	{	
		printf("%s \n", cmd_strarr[i]);
		// free(cmd_strarr[i]);
	}
	execve("/bin/awk", cmd_strarr + 1, NULL);
}
*/