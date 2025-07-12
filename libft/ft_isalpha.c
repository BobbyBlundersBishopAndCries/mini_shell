/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:43:40 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/21 16:55:37 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'));
}
/*
int main()
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
   return 0;
}*/
