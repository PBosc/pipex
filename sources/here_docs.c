/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 00:15:19 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/25 20:45:57 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_limit(char *line, char *limiter)
{
	int	length;

	length = ft_strlen(line) - 1;
	if (line[0] == '\n')
		return (0);
	return (ft_strncmp(line, limiter, length) == 0
		&& (line[length] == '\n'));
}

t_hered	*ft_hered_last(t_hered *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static int	ft_lstpush_back(t_hered **lst, char *line)
{
	t_hered	*new;

	new = malloc(sizeof(t_hered));
	if (!new)
		return (0);
	new->line = ft_strdup(line);
	new->next = NULL;
	if (lst)
	{
		if (*lst)
			ft_hered_last(*lst)->next = new;
		else
			*lst = new;
	}
	return (1);
}

t_hered	*read_here_doc(t_hered *here_doc, t_data *data)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (get_next_line(-42), perror("malloc"), NULL);
		if (is_limit(line, data->limiter))
			return (free(line), here_doc);
		if (!ft_lstpush_back(&here_doc, line))
			return (get_next_line(-42), perror("malloc list"), NULL);
	}
	return (NULL);
}

int	write_here_doc(t_hered *here_doc, t_data *data)
{
	t_hered	*node;

	node = here_doc;
	while (node)
	{
		write(data->pipe[1], node->line, ft_strlen(node->line));
		node = node->next;
	}
	return (1);
}
