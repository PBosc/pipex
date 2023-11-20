/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:29:22 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/09 19:54:43 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	j;
	size_t	i;

	if (*s2 == '\0')
		return ((char *) s1);
	i = 0;
	while (i < len && s1[i])
	{
		j = 0;
		while (i + j < len && s2[j] == s1[i + j])
		{
			j++;
			if (s2[j] == '\0')
				return ((char *) s1 + i);
		}
		i++;
	}
	return (NULL);
}
