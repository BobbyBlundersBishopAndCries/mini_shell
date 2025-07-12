/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:12:48 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/30 10:22:21 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
static char example_function(unsigned int index, char c) {
	index = 10;
	return c + 1;
}

int main() {
    const char *str = "hello";

    char *result = ft_strmapi(str, example_function);

    if (result) {
        printf("Original: %s\n", str);
        printf("Transformed: %s\n", result);
        free(result);
    } else {
        printf("Error in processing.\n");
    }
    return 0;
}*/
