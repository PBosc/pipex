/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 05:05:05 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/26 04:42:58 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static int	starts_with(char *str, char *start)
{
	int	i;

	i = 0;
	while (str[i] == start[i] && start[i])
		i++;
	if (start[i])
		return (0);
	return (1);
}

static char	*ft_trim(char *str, int start)
{
	char	*tmp;

	tmp = ft_strdup(str + start);
	free(str);
	return (tmp);
}

char	*get_valid_path(char **paths, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (starts_with(env[i], "PATH="))
		{
			path = ft_split(env[i], ':');
			path[0] = ft_trim(path[0], 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}
