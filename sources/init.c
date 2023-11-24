/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:50 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/24 03:05:44 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_heredoc(t_data *data)
{
	int			ret;
	t_hered		*heredoc;
	pid_t		child_pid;

	if (pipe(data->pipe) == -1)
		return (perror("pipe"), 0);
	heredoc = NULL;
	ret = read_here_doc(heredoc, data);
	if (!ret)
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
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		data->is_here_doc = 1;
		data->limiter = ft_strdup(argv[2]);
		init_heredoc(data);
	}
	else
		data->is_here_doc = 0;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->prev_pipe = -1;
	data->argv = argv;
	data->argc = argc;
	data->cmd_id = 2 + data->is_here_doc;
	data->env = env;
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
