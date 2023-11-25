/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:40:30 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/25 21:42:02 by pibosc           ###   ########.fr       */
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
