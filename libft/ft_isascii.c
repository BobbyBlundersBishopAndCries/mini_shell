/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:46:47 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/21 18:39:16 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
int	main(void)
{
		char test_chars[] = {'a', 'Z', '1', '!', ' ', 'z', 'A', 128, -1};
		int i = 0;
   while (i < 9)
	{
		char c = test_chars[i];
		if (ft_isascii(c))
		{
			printf("'%c' is an ascii character.\n", c);
		}
		else
		{
			printf("'%c' is NOT an ascii character.\n", c);
		}
	i++;
	}
   return (0);
}*/
