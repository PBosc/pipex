/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:31:45 by pibosc            #+#    #+#             */
/*   Updated: 2023/11/16 03:31:56 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

int	ft_puthexup_fd(size_t address, int fd, int size);
int	ft_putadd_fd(size_t address, int fd, int size);
int	ft_puthex_fd(unsigned int address, int fd, int size);
int	ft_puthexl_fd(size_t address, int fd, int size);
int	ft_putnbrc_fd(int n, int fd, int size);
int	ft_puthexl_fd(size_t address, int fd, int size);
int	ft_unbrc_fd(unsigned int n, int fd, int size);

#endif