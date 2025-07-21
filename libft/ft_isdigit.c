/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:58:14 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/21 18:39:19 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}
/*int main()
{
	char test_chars[] = {'5', 'Z', '1', '!', 63, 'z', '4', 128, -1};
		int i = 0;
   while (i < 9)
	{
		char c = test_chars[i];
		if (ft_isdigit(c))
		{
			printf("'%c' is a digit.\n", c);
		}
		else
		{
			printf("'%c' is NOT a digit.\n", c);
		}
	i++;
	}
   return (0);

}*/
