/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:34:35 by mohabid           #+#    #+#             */
/*   Updated: 2024/11/06 17:33:17 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void funfunction(unsigned int a, char *s)
{
	*s = *s + 1;
	(void)a;
}
int main()
{
	char *str = NULL;
	ft_striteri(str ,funfunction);
	printf("Output = %s\n",str);
	return 0;
}*/
