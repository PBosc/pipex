/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:50 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/26 03:21:45 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_heredoc(t_hered *heredoc, t_data *data)
{
	write_here_doc(heredoc, data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	free_heredoc(heredoc);
	free(data);
	exit(EXIT_SUCCESS);
}

int	init_heredoc(t_data *data)
{
	t_hered		*heredoc;
	pid_t		child_pid;
	int			ret;

	if (pipe(data->pipe) == -1)
		return (perror("pipe"), 0);
	heredoc = NULL;
	ret = read_here_doc(&heredoc, data);
	free(data->limiter);
	if (ret == 0)
		return (free_heredoc(heredoc), 0);
	child_pid = fork();
	if (child_pid == -1)
		return (free_heredoc(heredoc), 0);
	if (child_pid == 0)
		child_heredoc(heredoc, data);
	close(data->pipe[1]);
	data->prev_pipe = data->pipe[0];
	return (free_heredoc(heredoc), 1);
}

t_data	*init_args(t_data *data, int argc, char **argv, char **env)
{
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->prev_pipe = -1;
	data->argv = argv;
	data->argc = argc;
	data->env = env;
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		data->is_here_doc = 1;
		data->limiter = ft_strdup(argv[2]);
		init_heredoc(data);
	}
	else
	{
		data->is_here_doc = 0;
		data->limiter = NULL;
	}
	data->cmd_id = 2 + data->is_here_doc;
	return (data);
}

static int	ft_ends_with(char *str, char *end)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(end) - 1;
	while (j >= 0)
	{
		if (str[i] != end[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

int	check_args(t_data *data)
{
	if (data->argc < 5)
		return (ft_putstr_fd("Error: not enough arguments\n", STDERR_FILENO), 0);
	if (data->argc > 5 && !ft_ends_with(data->argv[0], "_bonus"))
		return (ft_putstr_fd("Error: too many arguments\n", STDERR_FILENO), 0);
	if (data->is_here_doc && ft_ends_with(data->argv[0], "_bonus"))
	{
		if (data->argc < 6)
			return (ft_putstr_fd("Error: not enough arguments\n",
					STDERR_FILENO), 0);
	}
	return (1);
}
