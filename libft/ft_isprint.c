/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:56:01 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/21 20:04:10 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int c)
{
	return (c <= 126 && c >= 32);
}
/*int main()
{
       	char test_chars[] = {'a', 'Z', '1', 14, ' ', 'z', 'A', 128, -1};
        int i = 0;
   while (i < 9)
    {
        char c = test_chars[i];
        if (ft_isprint(c))
        {
            printf("'%c' is a printable.\n", c);
        }
        else
        {
            printf("'%c' is NOT a printable.\n", c);
        }
	i++;
    }
   return 0;
}*/
