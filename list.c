/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:57:02 by roylee            #+#    #+#             */
/*   Updated: 2023/10/29 18:37:43 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**lst_to_strarr(t_list *lst)
{
	int		arrlen;
	int		i;
	t_list	*tmp;
	char	**array;

	arrlen = ft_lstsize(lst);
	array = malloc(sizeof(char *) * (arrlen + 1));
	if (!array)
	{
		free(array);
		return (NULL);
	}
	array[arrlen] = NULL;
	i = 0;
	while (i < arrlen)
	{
		array[i++] = (char *)lst->content;
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	return (array);
}
