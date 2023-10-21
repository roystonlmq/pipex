/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:12:15 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 14:25:18 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Closes read and write of pipe
*/
void	close_pipe(t_pipe *piper)
{
	close(piper->pipe[READ]);
	close(piper->pipe[WRITE]);
}

void	close_parent(t_pipe *piper)
{
	int	i;

	close(piper->infd);
	close(piper->outfd);
	i = 0;
	while (piper->cmd_paths[i])
		free(piper->cmd_paths[i++]);
	free(piper->cmd_paths);
}

void	close_child(t_pipe *piper)
{
	int	i;

	i = 0;
	while (piper->cmd_args[i])
		free(piper->cmd_args[i++]);
	free(piper->cmd_args);
	free(piper->cmd);
}

