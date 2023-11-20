/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:04:18 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/20 00:10:14 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"

typedef struct s_data {
	int		pipe[2];
	int		prev_pipe;
	char	**argv;
	int		argc;
	int		cmd_id;
	int		fd_in;
	int		fd_out;
	char	**env;
}	t_data;

t_data	*init_args(t_data *data, int argc, char **argv, char **env);

#endif