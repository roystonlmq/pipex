/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:54:22 by roylee            #+#    #+#             */
/*   Updated: 2023/10/29 05:27:33 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_quote(char c)
{
	if (c == '\'')
		return ((int)'\'');
	if (c == '\"')
		return ((int)'\"');
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

static char	*get_cmd(const char *s)
{
	int		i;
	char	*cmd;

	i = find_cmdidx(s);
	return (ft_substr(s, 0, i));
}

t_list	*parse_quote(const char *s, char *param)
{
	int		j;
	int		k;
	int		quote_type;

	quote_type = 0; // default: false
	s += find_cmdidx(s);
	j = 0;
	while (s[j++])
	{
		if (quote_type)
		{
			if (quote_type == is_quote(s[j]))
			{
				param = malloc(j - k + 2);
				if (!param)
					return (NULL);
				ft_strlcpy(param, s + k, j - k + 1);
			}
					
		}
		if (!quote_type)
		{
			if (is_quote(s[j]))
			{
				k = j + 1;
				quote_type = s[j];
			}
		}
	}
	return (ft_lstnew(param));
}

t_list	*cmd_split(const char *cmdstr)
{
	t_list	*cmd_list;
	char	*param;

	cmd_list = ft_lstnew(get_cmd(cmdstr));
	cmd_list->next = parse_quote(cmdstr, param);
	free(param);
	return (cmd_list);
}

int	main(void)
{
	t_list	*cmd_list;
	
	const char *teststr = "echo \"$USER | 'ici c'est Paris;\"";
	cmd_list = cmd_split(teststr);
	while (cmd_list)
	{
		printf("%s \n", (char *) cmd_list->content);
		cmd_list = cmd_list->next;
	}
}