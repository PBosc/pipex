/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:13:04 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/16 03:34:12 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	handle_flag(const char *f, va_list params)
{
	int	chars;

	chars = 0;
	if (*f == 'c' && ++chars)
		ft_putchar_fd((char) va_arg(params, int), 1);
	else if ((*f == 'd' || *f == 'i') && ++f)
		chars += ft_putnbrc_fd((int) va_arg(params, int), 1, 0);
	else if (*f == 'u' && ++f)
		chars += ft_unbrc_fd((unsigned int) va_arg(params, unsigned int), 1, 0);
	else if (*f == '%' && ++chars && ++f)
		ft_putchar_fd('%', 1);
	else if (*f == 'p' && ++f)
		chars += ft_putadd_fd((size_t) va_arg(params, size_t), 1, 0);
	else if (*f == 'x' && ++f)
		chars += ft_puthex_fd(
				(unsigned int) va_arg(params, unsigned int), 1, 0);
	else if (*f == 'X' && ++f)
		chars += ft_puthexup_fd(
				(unsigned int) va_arg(params, unsigned int), 1, 0);
	else if (*f == 's' && ++f)
		chars += ft_putstr_fd((char *) va_arg(params, char *), 1);
	return (chars);
}

int	ft_unbrc_fd(unsigned int n, int fd, int size)
{
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		return (1);
	}
	size = ft_unbrc_fd(n / 10, fd, size + 1);
	ft_putchar_fd(n % 10 + '0', fd);
	return (size + 1);
}

int	ft_printf(const char	*f, ...)
{
	va_list			params;
	char			c;
	int				chars;

	va_start(params, f);
	c = *f;
	chars = 0;
	while (*f)
	{
		c = *f;
		f++;
		if (c != '%')
		{
			ft_putchar_fd(c, 1);
			chars++;
			continue ;
		}
		chars += handle_flag(f++, params);
	}
	return (chars);
}
