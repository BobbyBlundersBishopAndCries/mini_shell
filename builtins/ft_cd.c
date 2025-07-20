/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:51:36 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/20 13:51:37 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd_vars(t_env *env, char *oldpwd, char *pwd)
{
	if (oldpwd)
		update_val(env, "OLDPWD", oldpwd);
	if (pwd)
		update_val(env, "PWD", pwd);
	free(oldpwd);
	free(pwd);
}

int	ft_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	int		count;

	if (!cmd || !cmd->env || !(*cmd->env))
		return (-1);
	count = arg_count(cmd->args);
	if (count > 2)
	{
		ft_printf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	pwd = cd_to_path(cmd, oldpwd);
	if (!pwd)
		return (1);
	update_pwd_vars(*cmd->env, oldpwd, pwd);
	return (0);
}
