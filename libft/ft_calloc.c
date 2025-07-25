/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:57:55 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/21 18:38:43 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (size != 0 && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	ptr = (unsigned char *)malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ptr[0] = 0;
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)(ptr));
}
/*
int	main(void) {
	// size_t n = 1;
	int *arr;
	arr = (int *)calloc(0,0);
	if(!arr)
	{
		printf("Memory allocation fails");
		return (1);
	}
	free(arr);
	// arr = (int *)ft_calloc(0, 0);
	// if (arr == NULL) {
	// 	printf("Memory allocation failed.\n");
	// 	return (1);
	// }
	// free(arr);
	return (0);
}*/