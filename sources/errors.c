/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 05:24:40 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/02 14:32:57 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input(t_data *data)
{
	if (access(data->argv[1], F_OK) == -1
		|| (access(data->argv[1], F_OK) == 0
			&& access(data->argv[1], R_OK) == -1))
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
		}
		else
		{
			free(path);
			free_tab_2d(cmd);
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
	if (access(data->argv[1], F_OK) == -1
		|| (access(data->argv[1], F_OK) == 0
			&& access(data->argv[1], R_OK) == -1))
		is_input = 1;
	check_commands(data, is_output, is_input);
	if (is_output)
	{
		ft_putstr_fd(data->argv[data->argc - 1], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	check_input(data);
}
