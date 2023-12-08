/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 05:24:40 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/08 13:49:39 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input(t_data *data)
{
	if (!data->is_here_doc && (access(data->argv[1], F_OK) == -1
			|| (access(data->argv[1], F_OK) == 0
				&& access(data->argv[1], R_OK) == -1)))
		perror(data->argv[1]);
}

void	check_commands(t_data *data, int is_output, int is_input)
{
	int		i;
	char	**cmd;
	char	*path;

	i = data->cmd_id - 1 + is_input;
	while (++i < data->argc - 1 - is_output)
	{
		cmd = ft_split(data->argv[i], ' ');
		path = get_valid_path(get_path(data->env), cmd[0]);
		if (!path)
		{
			ft_putstr_fd(cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			free_tab_2d(cmd);
			if (errno == ENOTDIR || errno == EISDIR)
				data->ret_value = 126;
			else
				data->ret_value = 127;
			data->failed = 1;
		}
		else
		{
			free(path);
			free_tab_2d(cmd);
			data->failed = 0;
			data->ret_value = 0;
		}
	}
}

void	check_errors(t_data *data)
{
	int	is_output;
	int	is_input;

	is_output = 0;
	is_input = 0;
	if (access(data->argv[data->argc - 1], F_OK) == 0
		&& access(data->argv[data->argc - 1], W_OK) == -1)
		is_output = 1;
	if (data->is_here_doc || (access(data->argv[1], F_OK) == -1
			|| (access(data->argv[1], F_OK) == 0
				&& access(data->argv[1], R_OK) == -1)))
		is_input = 1;
	check_commands(data, is_output, is_input);
	if (is_output)
	{
		ft_putstr_fd(data->argv[data->argc - 1], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	check_input(data);
}

int	wait_commands(t_data *data, pid_t pid)
{
	data->waitpid = 0;
	data->status = 0;
	while (1)
	{
		data->status = 0;
		data->waitpid = wait(&data->status);
		if (data->waitpid == -1)
			break ;
		if (data->waitpid != pid || data->ret_value != EXIT_SUCCESS)
			continue ;
		if (WIFEXITED(data->status) && data->failed == 0)
			data->ret_value = WEXITSTATUS(data->status);
		else if (data->failed == 0)
			data->ret_value = 128 + WTERMSIG(data->status);
	}
	return (data->ret_value);
}
