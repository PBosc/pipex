/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:04:41 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/20 20:38:15 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	pipes(t_data *data)
{
	if (data->cmd_id == 0)
	{
		data->fd_in = open(data->argv[0], O_RDONLY);
		if (data->fd_in == -1)
			return (perror("open"), -1);
		dup2(data->fd_in, STDIN_FILENO);
	}
	else
		dup2(data->prev_pipe, STDIN_FILENO);
	if (data->cmd_id == data->argc - 3)
	{
		data->fd_out = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 666);
		if (data->fd_out == -1)
			return (perror("open"), -1);
		dup2(data->fd_out, STDOUT_FILENO);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
}

int	pipex(t_data *data)
{
	pid_t	pid;

	if (pipe(data->pipe) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	pid = fork();
	if (!pid)
	{
		pipes(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!init_args(data, argc, argv, env))
		return (free(data), EXIT_FAILURE);
	return (0);
}
