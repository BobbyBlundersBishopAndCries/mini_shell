/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:36:06 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/21 19:44:45 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c <= '9' && c >= '0') || ((c >= 'A' && c <= 'Z') \
			|| (c >= 'a' && c <= 'z')));
}
/*
int main()
{
       	char test_chars[] = {'a', 'Z', '1', '!', ' ', 'z', 'A', 128, -1};
        int i = 0;
   while (i < 9)
    {
        char c = test_chars[i];
        if (ft_isalnum(c))
        {
            printf("'%c' is an alphabet or a digit.\n", c);
        }
        else
        {
            printf("'%c' is NOT an alphabet nor a digit.\n", c);
        }
	i++;
    }
   return 0;
}
*/
