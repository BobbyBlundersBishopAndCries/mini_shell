/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:31 by feedback          #+#    #+#             */
/*   Updated: 2025/07/14 18:12:29 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_or_builtin(t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
	{
		g_shell.exit_status = execute_builtin(cmd);
		exit(g_shell.exit_status);
	}
	execute_command(cmd);
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

static void	child_process_execution(t_cmd *cmd, int prev_fd[2], int next_fd[2])
{
	restore_signals_to_default();
	setup_child_fds(cmd, prev_fd, next_fd);
	if (setup_redirections(cmd->files))
		exit(EXIT_FAILURE);
	close_redirs(cmd->files);
	exec_or_builtin(cmd);
}

static void	fork_and_execute(t_cmd *cmd, int prev_fd[2])
{
	int		next_fd[2] = {-1, -1};
	pid_t	pid;

	if (cmd->next && pipe(next_fd) == -1)
		error();

	g_shell.child_running = 1;

	pid = fork();
	if (pid < 0)
		error();

	if (pid == 0)
		child_process_execution(cmd, prev_fd, next_fd);

	// Parent process:
	if (prev_fd[0] != -1)
		close(prev_fd[0]); // close old read end

	if (cmd->next)
	{
		prev_fd[0] = next_fd[0];  // keep new read end
		close(next_fd[1]);        // close write end
	}
	else
		prev_fd[0] = -1;
}
void	execute_pipeline(t_cmd *cmd)
{
	int		prev_fd[2];
	t_cmd	*tmp;

	prev_fd[0] = -1;
	prev_fd[1] = -1;
	if (handle_all_heredocs(cmd))
		return ;
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		// Close any heredoc pipe read fds to prevent leaks
		t_redir *r = cmd->files;
		while (r)
		{
			if (r->index == R_HEREDOC && r->fd > 2)
				close(r->fd);
			r = r->next;
		}
		g_shell.exit_status = 0;
		return;
	}
	tmp = cmd;
	while (tmp)
	{
		fork_and_execute(tmp, prev_fd);
		tmp = tmp->next;
	}
	handle_signals();
	wait_for_children();
	g_shell.child_running = 0;
}
