/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:40:10 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 14:24:17 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strdup(const char *s)
{
	int		i;
	char	*buffer;

	buffer = (char *)malloc(ft_strlen(s)+ 1);
	if (!buffer)
		return (0);
	i = -1;
	while (s[++i])
		buffer[i] = s[i];
	buffer[i] = 0;
	return (buffer);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*buffer;

	len = ft_strlen(s1) + ft_strlen(s2);
	buffer = (char *)malloc(len + 1);
	if (!buffer)
		return (0);
	i = -1;
	while (s1[++i])
		buffer[i] = s1[i];
	j = -1;
	while (s2[++j])
		buffer[i + j] = s2[j];
	buffer[i + j] = 0;
	return (buffer);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*buffer;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	buffer = (char *)malloc(len + 1);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s + start, len + 1);
	return (buffer);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	slen;

	slen = ft_strlen(src);
	if (size > slen + 1)
		ft_memcpy(dst, src, slen + 1);
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (slen);
}
