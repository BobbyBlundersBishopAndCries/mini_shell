/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:43:40 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/21 18:39:13 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'));
}
/*
int	main(void)
{
		char test_chars[] = {'a', 'Z', '1', '!', ' ', 'z', 'A', 128, -1};
		int i = 0;
   while (i < 9)
	{
		char c = test_chars[i];
		if (ft_isalpha(c))
		{
			printf("'%c' is an alphabet.\n", c);
		}
		else
		{
			printf("'%c' is NOT an alphabet.\n", c);
		}
	i++;
	}
   return (0);
}*/
