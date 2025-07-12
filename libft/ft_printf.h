/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:03:39 by mohabid           #+#    #+#             */
/*   Updated: 2024/11/15 10:52:20 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <limits.h>
# include <unistd.h>

int	ft_putchar(int c, int fd);
int	ft_putstr(const char *s, int fd);
int	ft_putnbr_lower(long n, int base, int fd);
int	ft_putnbr_upper(long n, int base, int fd);
int	ft_print_format(char spec, va_list ap, int fd);
int	ft_putnbr_pointer(unsigned long n, unsigned int base, int fd);
int	ft_printf(int fd, const char *s, ...);
#endif
