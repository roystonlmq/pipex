/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roylee <roylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:12:15 by roylee            #+#    #+#             */
/*   Updated: 2023/10/14 13:41:38 by roylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	close_all(t_pipe *piper)
{
	close(piper->pipe[0]);
	close(piper->pipe[1]);
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
