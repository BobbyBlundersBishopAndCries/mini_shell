/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:03:21 by mohabid           #+#    #+#             */
/*   Updated: 2024/11/01 09:27:23 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_number_size(int number)
{
	size_t	length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		length += 1;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*string;
	size_t	length;

	length = ft_number_size(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	string = (char *)malloc(sizeof(char) * length + 1);
	if (string == NULL)
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		n = -n;
	}
	if (n == 0)
		string[0] = '0';
	string[length] = '\0';
	while (n != 0)
	{
		string[length - 1] = (n % 10) + '0';
		n = n / 10;
		length--;
	}
	return (string);
}
/*
int	main(void)
{
	int		n;
	char	*str;

	n = 5459;
	str = ft_itoa(n);
	printf("%s \n", str);
	free(str);
	return (0);
}*/
