/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:13:40 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/12 18:18:35 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *(unsigned char *)(s + i) != (unsigned char)c
		&& *(unsigned char *)(s + i))
		i++;
	if (*(unsigned char *)(s + i) == (unsigned char)c && i < n)
		return ((void *)(s + i));
	return (NULL);
}
