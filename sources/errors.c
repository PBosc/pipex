/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 05:24:40 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/30 06:06:03 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_errors(t_data *data)
{
	int		is_output;
	int		i;
	char	**cmd;
	char	*path;

	is_output = 0;
	i = -1;
	if (access(data->argv[data->argc - 1], F_OK) == 0
		&& access(data->argv[data->argc - 1], W_OK) == -1)
		is_output = 1;
	while (++i < data->argc - 1 - is_output)
	{
		cmd = ft_split(data->argv[i], ' ');
		path = get_valid_path(get_path(data->env), cmd[0]);
		if (!path)
		{
			ft_putstr_fd(cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		}
	}
	if (is_output)
	{
		ft_putstr_fd(data->argv[data->argc - 1], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	if (access(data->argv[1], F_OK) == -1 || (access(data->argv[1], F_OK) == 0
			&& access(data->argv[1], R_OK) == -1))
		perror(data->argv[1]);
}
