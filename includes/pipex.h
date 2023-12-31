/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:04:18 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/08 13:29:14 by pibosc           ###   ########.fr       */
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
	int		is_here_doc;
	char	*limiter;
	char	*path;
	pid_t	waitpid;
	int		status;
	int		ret_value;
	int		failed;
}	t_data;

typedef struct s_hered {
	char			*line;
	struct s_hered	*next;
}	t_hered;

t_data		*init_args(t_data *data, int argc, char **argv, char **env);
void		free_tab_2d(char **tab);
char		**get_path(char **env);
char		*get_valid_path(char **paths, char *cmd);
int			read_here_doc(t_hered **here_doc, t_data *data);
int			write_here_doc(t_hered *here_doc, t_data *data);
int			check_args(t_data *data);
void		free_heredoc(t_hered *here_doc);
int			handle_process(t_data *data, char *path, char **cmd, int pid);
int			child_pipes(t_data *data);
int			exec(t_data *data, char *path, char **cmd);
void		check_errors(t_data *data);
int			wait_commands(t_data *data, pid_t pid);

#endif