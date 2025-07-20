/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:43:39 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/20 13:43:44 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*abs_path;

	abs_path = getcwd(NULL, 0);
	if (!abs_path)
	{
		ft_printf(STDERR_FILENO, "pwd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_printf(STDOUT_FILENO, "%s\n", abs_path);
	free(abs_path);
	return (EXIT_SUCCESS);
}
