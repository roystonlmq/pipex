/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:49:28 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 14:21:49 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static int	ft_word_count(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			s += ft_word_len(s, c);
		}
		else
			s++;
	}
	return (i);
}

static void	*ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	int		i;
	int		wd_count;

	i = 0;
	if (!s)
		return (NULL);
	wd_count = ft_word_count(s, c);
	ret = (char **)malloc((wd_count + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[wd_count] = 0;
	while (*s)
	{
		if (*s != c)
		{
			ret[i] = ft_substr(s, 0, ft_word_len(s, c));
			if (!ret[i++])
				return (ft_free(ret));
			s += ft_word_len(s, c);
		}
		else
			s++;
	}
	return (ret);
}
