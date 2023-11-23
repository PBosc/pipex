/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:50 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/23 01:55:30 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*init_args(t_data *data, int argc, char **argv, char **env)
{
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->prev_pipe = -1;
	data->argv = argv;
	data->argc = argc;
	data->cmd_id = 2;
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
