/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:26 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:52:26 by feedback         ###   ########.fr       */
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
		|| ft_strcmp(cmd, "!") == 0);
}

int	apply_redirections(t_redir *redir_list, int *saved_stdout, int *saved_stdin)
{
	t_redir	*tmp;

	tmp = redir_list;
	while (tmp)
	{
		tmp->fd = open_file(tmp, tmp->index);
		if (tmp->fd < 0)
			return (perror("open"), -1);
		if ((tmp->index == R_OUT || tmp->index == R_APPEND) && *saved_stdout ==
			-1)
			*saved_stdout = dup(STDOUT_FILENO);
		if ((tmp->index == R_IN || tmp->index == R_HEREDOC) && *saved_stdin ==
			-1)
			*saved_stdin = dup(STDIN_FILENO);
		if (tmp->index == R_OUT || tmp->index == R_APPEND)
		{
			if (dup2(tmp->fd, STDOUT_FILENO) < 0)
				return (perror("dup2 out"), -1);
		}
		else if (tmp->index == R_IN || tmp->index == R_HEREDOC)
		{
			if (dup2(tmp->fd, STDIN_FILENO) < 0)
				return (perror("dup2 in"), -1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	restore_redirections(int saved_stdout, int saved_stdin)
{
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

static int	handle_builtin_cmd(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(cmd));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd));
	if (ft_strcmp(cmd->args[0], ":") == 0)
		return (0);
	return (1);
}

static void	refresh_envp_if_needed(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "export") == 0 || ft_strcmp(cmd->args[0],
			"unset") == 0)
	{
		if (cmd->envp)
			free_array(cmd->envp);
		cmd->envp = env_tochar(*(cmd->env));
	}
}

int	execute_builtin(t_cmd *cmd)
{
	int	status;
	int	saved_stdout;
	int	saved_stdin;

	saved_stdin = -1;
	saved_stdout = -1;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (apply_redirections(cmd->files, &saved_stdout, &saved_stdin) < 0)
		return (1);
	if (!is_builtin(cmd->args[0]))
		return (1);
	status = handle_builtin_cmd(cmd);
	refresh_envp_if_needed(cmd);
	restore_redirections(saved_stdout, saved_stdin);
	return (status);
}
