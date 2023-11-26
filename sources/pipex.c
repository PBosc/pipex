/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:04:41 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/26 04:57:50 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static int	get_fd_out(t_data *data)
{
	if (!data->is_here_doc)
		data->fd_out = open(data->argv[data->argc - 1], O_WRONLY
				| O_CREAT | O_TRUNC, 0666);
	else
		data->fd_out = open(data->argv[data->argc - 1], O_WRONLY
				| O_CREAT | O_APPEND, 0666);
	return (data->fd_out);
}

static int	child_pipes(t_data *data)
{
	if (data->cmd_id == 2)
	{
		data->fd_in = open(data->argv[1], O_RDONLY);
		if (data->fd_in == -1)
			return (perror("open"), EXIT_FAILURE);
		dup2(data->fd_in, STDIN_FILENO);
	}
	else
		dup2(data->prev_pipe, STDIN_FILENO);
	if (data->cmd_id == data->argc - 2)
	{
		data->fd_out = get_fd_out(data);
		if (data->fd_out == -1)
			return (perror("open"), EXIT_FAILURE);
		dup2(data->fd_out, STDOUT_FILENO);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	close(data->pipe[0]);
	data->is_here_doc = 0;
	return (EXIT_SUCCESS);
}

static int	exec(t_data *data)
{
	char	**cmd;
	char	**paths;

	cmd = ft_split(data->argv[data->cmd_id], ' ');
	paths = get_path(data->env);
	cmd[0] = get_valid_path(paths, cmd[0]);
	if (!cmd[0])
	{	
		ft_putstr_fd(data->argv[data->cmd_id], STDERR_FILENO),
		ft_putstr_fd(": command not found\n", STDERR_FILENO),
		free_tab_2d(cmd);
		exit(EXIT_FAILURE);
	}
	execve(cmd[0], cmd, data->env);
	free_tab_2d(cmd);
	return (EXIT_SUCCESS);
}

static int	pipex(t_data *data)
{
	pid_t	pid;
	int		status;

	while (data->cmd_id < data->argc - 1)
	{
		if (pipe(data->pipe) == -1)
			return (perror("pipe"), EXIT_FAILURE);
		pid = fork();
		if (!pid)
		{
			if (child_pipes(data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			exec(data);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (data->prev_pipe != -1)
				close(data->prev_pipe);
			data->prev_pipe = data->pipe[0];
			close(data->pipe[1]);
			wait(&status);
			if (WIFEXITED(status))
				if (WEXITSTATUS(status) == EXIT_FAILURE)
					exit(EXIT_FAILURE);
		}
		++data->cmd_id;
	}
	return (wait(&status), EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("malloc"), EXIT_FAILURE);
	if (!init_args(data, argc, argv, env))
		return (free(data), EXIT_FAILURE);
	if (!check_args(data))
		return (free(data), EXIT_FAILURE);
	pipex(data);
	free(data);
	return (0);
}
