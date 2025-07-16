/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:31 by feedback          #+#    #+#             */
/*   Updated: 2025/07/16 11:14:18 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_or_builtin(t_cmd *cmd, t_lst_cmd *head)
{
	if (is_builtin(cmd->args[0]))
	{
		g_shell.exit_status = execute_builtin(cmd);
		{
			t_cmd *tmp;
			tmp = head->head;
			while (tmp)
			{
				free_array(tmp->envp);
				tmp = tmp->next;
			}
		free_all(head->k);
			exit(g_shell.exit_status);
		}
	}
	execute_command(cmd, head);
	exit(EXIT_FAILURE);
}

static void	setup_child_fds(t_cmd *cmd, int prev_fd[2], int next_fd[2])
{
	if (prev_fd[0] != -1)
	{
		dup2(prev_fd[0], STDIN_FILENO);
		close(prev_fd[0]);
	}
	if (cmd->next)
	{
		close(next_fd[0]);
		dup2(next_fd[1], STDOUT_FILENO);
		close(next_fd[1]);
	}
}

static void	child_process_execution(t_cmd *cmd, int prev_fd[2], int next_fd[2] , t_lst_cmd *head)
{
	restore_signals_to_default();
	setup_child_fds(cmd, prev_fd, next_fd);
	if (setup_redirections(cmd->files))
	{
		t_cmd *tmp;
		tmp = head->head;
		while(tmp)
		{
			free_array(tmp->envp);
			tmp = tmp->next;
		}
		free_all(head->k);
		exit(EXIT_FAILURE);
	}
	close_redirs(cmd->files);
	exec_or_builtin(cmd, head);
}

static void	fork_and_execute(t_cmd *cmd, int prev_fd[2] , t_lst_cmd *head)
{
	int		next_fd[2];
	pid_t	pid;

	next_fd[0] = -1;
	next_fd[1] = -1;
	if (cmd->next && pipe(next_fd) == -1)
		error();
	g_shell.child_running = 1;
	pid = fork();
	if (pid < 0)
		error();
	if (pid == 0)
		child_process_execution(cmd, prev_fd, next_fd, head);
	if (prev_fd[0] != -1)
		close(prev_fd[0]);
	if (cmd->next)
	{
		prev_fd[0] = next_fd[0];
		close(next_fd[1]);
	}
	else
		prev_fd[0] = -1;
}

void	execute_pipeline(t_cmd *cmd , t_lst_cmd *head)
{
	int		prev_fd[2];
	t_cmd	*tmp;
	t_redir	*r;

	prev_fd[0] = -1;
	prev_fd[1] = -1;
	if (handle_all_heredocs(cmd))
		return ;
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		r = cmd->files;
		while (r)
		{
			if (r->index == R_HEREDOC && r->fd > 2)
				close(r->fd);
			r = r->next;
		}
		g_shell.exit_status = 0;
		return ;
	}
	tmp = cmd;
	while (tmp)
	{
		fork_and_execute(tmp, prev_fd , head);
		tmp = tmp->next;
	}
	handle_signals();
	wait_for_children();
	g_shell.child_running = 0;
}
