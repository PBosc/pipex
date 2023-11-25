/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:50 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/25 21:02:43 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_heredoc(t_data *data)
{
	t_hered		*heredoc;
	pid_t		child_pid;

	if (pipe(data->pipe) == -1)
		return (perror("pipe"), 0);
	heredoc = NULL;
	heredoc = read_here_doc(heredoc, data);
	if (!heredoc)
		return (0);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
	{
		write_here_doc(heredoc, data);
		get_next_line(-42);
		close(data->pipe[0]);
		close(data->pipe[1]);
		exit(EXIT_SUCCESS);
	}
	get_next_line(-42);
	close(data->pipe[1]);
	data->prev_pipe = data->pipe[0];
	return (1);
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
		data->is_here_doc = 0;
	data->cmd_id = 2 + data->is_here_doc;
	return (data);
}

void	free_tab_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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