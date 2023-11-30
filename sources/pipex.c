/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:04:41 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/30 02:05:34 by pibosc           ###   ########.fr       */
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

int	child_pipes(t_data *data)
{
	if (data->cmd_id == 2)
	{
		data->fd_in = open(data->argv[1], O_RDONLY);
		if (data->fd_in == -1)
			return (perror(data->argv[1]), EXIT_FAILURE);
		dup2(data->fd_in, STDIN_FILENO);
	}
	else
		dup2(data->prev_pipe, STDIN_FILENO);
	if (data->cmd_id == data->argc - 2)
	{
		data->fd_out = get_fd_out(data);
		if (data->fd_out == -1)
			return (perror(data->argv[data->argc - 1]), EXIT_FAILURE);
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

int	exec(t_data *data, char *path, char **cmd)
{
	cmd[0] = ft_strdup(path);
	free(path);
	if (!cmd[0] || access(cmd[0], F_OK) == -1)
	{
		free_tab_2d(cmd);
		data->failed = 1;
		exit(EXIT_FAILURE);
	}
	execve(cmd[0], cmd, data->env);
	return (EXIT_FAILURE);
}

static int	pipex(t_data *data)
{
	pid_t	pid;
	int		status;
	char	**cmd;
	char	*path;

	while (data->cmd_id < data->argc - 1 && !data->failed)
	{
		cmd = ft_split(data->argv[data->cmd_id], ' ');
		path = get_valid_path(get_path(data->env), cmd[0]);
		if (!path)
			return (free_tab_2d(cmd), EXIT_FAILURE);
		if (pipe(data->pipe) == -1)
			return (free_tab_2d(cmd), perror("pipe"), EXIT_FAILURE);
		pid = fork();
		if (!handle_process(data, path, cmd, pid))
			return (free(path), free_tab_2d(cmd), EXIT_FAILURE);
		free(path);
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
	pipex(data);
	free(data);
	return (0);
}
