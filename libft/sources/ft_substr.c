/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:38:10 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/12 17:42:24 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	size;

	if (s == NULL)
		return (NULL);
	if ((size_t)start >= ft_strlen(s) || len == 0)
		size = 1;
	else if (ft_strlen(s + start) > len)
		size = len + 1;
	else
		size = ft_strlen(s + start) + 1;
	tmp = (char *)malloc(sizeof(char) * size);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < (size - 1) && s[(size_t)start + i])
	{
		tmp[i] = s[(size_t)start + i];
		++i;
	}
	tmp[i] = '\0';
	return (tmp);
}
