/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:23:50 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/20 01:29:51 by pibosc           ###   ########.fr       */
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
	data->cmd_id = 0;
	data->env = env;
}
