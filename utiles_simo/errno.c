/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:49:14 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/21 18:40:12 by mlakhdar         ###   ########.fr       */
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

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

int	exec_error_status(int err)
{
	if (err == EACCES || err == ENOEXEC || err == ETXTBSY)
		return (126);
	if (err == ENOENT || err == ENOTDIR)
		return (127);
	return (1);
}

char	**return_path(t_env *env)
{
	char	*path_value;
	char	**path;

	path_value = get_value(env, "PATH");
	if (!path_value)
		return (NULL);
	path = ft_split(path_value, ':');
	free(path_value);
	if (!path)
		return (NULL);
	return (path);
}
