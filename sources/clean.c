/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:40:30 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/30 02:24:33 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_heredoc(t_hered *here_doc)
{
	t_hered	*tmp;

	while (here_doc)
	{
		tmp = here_doc;
		here_doc = here_doc->next;
		free(tmp->line);
		free(tmp);
	}
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

int	handle_process(t_data *data, int pid)
{
	char	**cmd;
	char	*path;

	if (!pid)
	{
		if (child_pipes(data) == EXIT_FAILURE)
			return (0);
		cmd = ft_split(data->argv[data->cmd_id], ' ');
		if (!cmd)
			return (EXIT_FAILURE);
		path = get_valid_path(get_path(data->env), cmd[0]);
		if (!path)
			return (free_tab_2d(cmd), EXIT_FAILURE);
		exec(data, path, cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (data->prev_pipe != -1)
			close(data->prev_pipe);
		data->prev_pipe = data->pipe[0];
		close(data->pipe[1]);
	}
	return (1);
}
