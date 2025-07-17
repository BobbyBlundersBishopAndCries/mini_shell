/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:32 by feedback          #+#    #+#             */
/*   Updated: 2025/07/17 13:15:59 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, ":") == 0
		|| ft_strcmp(cmd, "!") == 0 || ft_strcmp(cmd, ":") == 0);
}

int	handle_builtin_cmd(t_cmd *cmd, t_lst_cmd *head)
{
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(cmd));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd, head));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd));
	if (ft_strcmp(cmd->args[0], ":") == 0)
		return (0);
	if (ft_strcmp(cmd->args[0], "!") == 0)
		return (0);
	return (1);
}

int	exec_error_status(int err)
{
	if (err == EACCES || err == ENOEXEC || err == ETXTBSY)
		return (126);
	if (err == ENOENT || err == ENOTDIR)
		return (127);
	return (1);
}
