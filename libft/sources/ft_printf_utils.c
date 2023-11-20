/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:34:11 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/16 03:31:23 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrc_fd(int n, int fd, int size)
{
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		return (ft_putnbrc_fd(-n, fd, size) + 1);
	}
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		return (1);
	}
	size += ft_putnbrc_fd(n / 10, fd, size);
	ft_putchar_fd(n % 10 + '0', fd);
	return (size + 1);
}

int	ft_puthex_fd(unsigned int address, int fd, int size)
{
	if (address < 16)
	{
		ft_putchar_fd(HEX_BASE_LOW[address % 16], fd);
		return (1);
	}
	size = ft_puthex_fd(address / 16, fd, size + 1);
	ft_putchar_fd(HEX_BASE_LOW[address % 16], fd);
	return (size + 1);
}

int	ft_putadd_fd(size_t address, int fd, int size)
{
	if (!address)
		return (ft_putstr_fd("(nil)", 1));
	if (!size)
		size += ft_putstr_fd("0x", 1);
	size += ft_puthexl_fd(address, fd, size + 1);
	return (size);
}

int	ft_puthexup_fd(size_t address, int fd, int size)
{
	if (address < 16)
	{
		ft_putchar_fd(HEX_BASE_UP[address % 16], fd);
		return (1);
	}
	size = ft_puthexup_fd(address / 16, fd, size + 1);
	ft_putchar_fd(HEX_BASE_UP[address % 16], fd);
	return (size + 1);
}

int	ft_puthexl_fd(size_t address, int fd, int size)
{
	if (address < 16)
	{
		ft_putchar_fd(HEX_BASE_LOW[address % 16], fd);
		return (1);
	}
	size = ft_puthexl_fd(address / 16, fd, size + 1);
	ft_putchar_fd(HEX_BASE_LOW[address % 16], fd);
	return (size + 1);
}
