/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:46:47 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/21 19:53:11 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
int main()
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
   return 0;
}*/
