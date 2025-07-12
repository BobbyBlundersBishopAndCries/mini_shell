/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:13:39 by mohabid           #+#    #+#             */
/*   Updated: 2025/01/17 22:08:32 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr(const char *s, int fd)
{
	int	count;

	if (s == NULL)
		return (ft_putstr("(null)", fd));
	count = 0;
	while (*s)
	{
		count += ft_putchar(*s++, fd);
	}
	return (count);
}
