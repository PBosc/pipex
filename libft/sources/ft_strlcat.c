/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:17:47 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/12 16:46:17 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	if ((!dst || !src) && !dstsize)
		return (0);
	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (len_dest > dstsize - 1)
		return (dstsize + len_src);
	if (dstsize == 0)
		return (len_src);
	while (i < dstsize - len_dest - 1 && src[i])
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	return (len_dest + len_src);
}
