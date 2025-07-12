/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:29 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:52:29 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static char	**return_path(t_env *env)
{
	char	*path_value;
	char	**path;

	path_value = get_value(env, "PATH");
	if (!path_value)
		return (NULL);
	path = ft_split(path_value, ':');
	if (!path)
		return (NULL);
	return (path);
}

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

static char	*resolve_exec_path(t_cmd *cmd)
{
	char	*p;
	char	*tmp;

	if (cmd->args[0][0] == '/')
		return (ft_strdup(cmd->args[0]));
	if (cmd->args[0][0] == '.')
	{
		tmp = getcwd(NULL, 0);
		p = strjoin_val_path(tmp, cmd->args[0], 1);
		free(tmp);
		return (p);
	}
	if (cmd->args[0][0] == '~')
		return (strjoin_val_path(get_value(*(cmd->env), "HOME"), cmd->args[0]
				+ 1, 1));
	return (path_found(*(cmd->env), cmd->args[0]));
}

void	execute_command(t_cmd *cmd)
{
	char	*p;

	if (!cmd || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
		return ;
	if (is_directory(cmd->args[0]))
	{
		ft_printf(2, "minishell: %s: Is a directory\n", cmd->args[0]);
		exit(126);
	}
	p = resolve_exec_path(cmd);
	if (!p)
	{
		ft_printf(2, "minishell: %s: command not found\n", cmd->args[0]);
		exit(127);
	}
	execve(p, cmd->args, cmd->envp);
	ft_printf(2, "minishell: %s: %s\n", cmd->args[0], strerror(errno));
	exit(exec_error_status(errno));
}
