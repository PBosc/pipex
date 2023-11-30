/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:40:30 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/30 04:50:37 by pibosc           ###   ########.fr       */
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

int	handle_process(t_data *data, char *path, char **cmd, int pid)
{
	if (!pid)
	{
		if (child_pipes(data) == EXIT_FAILURE)
			return (0);
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
	free_tab_2d(cmd);
	return (1);
}
