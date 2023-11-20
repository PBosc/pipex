/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:24:58 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/09 18:24:58 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strchr_chr(const char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static size_t	end(char const *s1, char const *set)
{
	size_t	end;

	end = ft_strlen(s1) - 1;
	while (ft_strchr_chr(s1[end], set))
		end--;
	return (end + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;
	size_t	j;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = end(s1, set);
	while (s1[i] && len)
	{
		if (!ft_strchr_chr(s1[i++], set))
			break ;
		len--;
	}
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	i--;
	j = 0;
	while (s1[i] && j < len)
		ret[j++] = s1[i++];
	ret[j] = '\0';
	return (ret);
}
