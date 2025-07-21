/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:36:11 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/21 18:37:55 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*path_found(t_env *env, char *cmd)
{
	char	**path;
	char	*full_path;
	int		i;

	path = return_path(env);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		full_path = strjoin_val_path(path[i], cmd, 1);
		if (access(full_path, X_OK) == 0)
		{
			free_array(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(path);
	return (NULL);
}

static char	*resolve_home_path(t_cmd *cmd)
{
	char	*tmp;
	char	*full;

	tmp = get_value(*(cmd->env), "HOME");
	if (!tmp)
		return (NULL);
	full = strjoin_val_path(tmp, cmd->args[0] + 1, 1);
	free(tmp);
	return (full);
}

static char	*resolve_relative_path(t_cmd *cmd)
{
	char	*tmp;
	char	*full;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (NULL);
	full = strjoin_val_path(tmp, cmd->args[0], 1);
	free(tmp);
	return (full);
}

static char	*resolve_exec_path(t_cmd *cmd)
{
	if (cmd->args[0][0] == '/')
		return (ft_strdup(cmd->args[0]));
	if (ft_strncmp(cmd->args[0], "./", 2) == 0
		|| ft_strncmp(cmd->args[0], "../", 3) == 0)
		return (resolve_relative_path(cmd));
	if (cmd->args[0][0] == '~')
		return (resolve_home_path(cmd));
	if (is_directory(cmd->args[0])
		&& cmd->args[0][ft_strlen(cmd->args[0]) - 1] == '/')
		return (ft_strdup(cmd->args[0]));
	return (path_found(*(cmd->env), cmd->args[0]));
}

void	execute_command(t_cmd *cmd, t_lst_cmd *head)
{
	char	*p;

	if (!cmd || !cmd->args)
		return ;
	p = resolve_exec_path(cmd);
	if (!p || ft_strcmp(cmd->args[0], "") == 0)
	{
		ft_printf(2, "minishell: %s: command not found\n", cmd->args[0]);
		free_shellax(head);
		exit(127);
	}
	if (is_directory(cmd->args[0]))
	{
		ft_printf(2, "minishell: %s: Is a directory\n", cmd->args[0]);
		free_shellax(head);
		exit(126);
	}
	execve(p, cmd->args, cmd->envp);
	ft_printf(2, "minishell: %s: %s\n", cmd->args[0], strerror(errno));
	free_shellax(head);
	free(p);
	exit(exec_error_status(errno));
}
