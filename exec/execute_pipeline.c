/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:02:14 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/17 18:39:46 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../minishell.h"

static void	last_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		g_shell.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			ft_printf(STDOUT_FILENO, "Quit (core dumped)\n");
		g_shell.exit_status = 128 + sig;
	}
}

static void	wait_for_pipeline(pid_t *pids, int count)
{
	int	status;
	int	i;

	i = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			i++;
			continue ;
		}
		if (i == count - 1)
			last_status(status);
		i++;
	}
}

static bool	validate_pipeline(t_cmd *cmd)
{
	t_redir	*r;

	if (handle_all_heredocs(cmd))
		return (false);
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		if (cmd != NULL)
			r = cmd->files;
		else
			r = NULL;
		while (r)
		{
			if (r->index == R_HEREDOC && r->fd > 2)
				close(r->fd);
			r = r->next;
		}
		g_shell.exit_status = 0;
		return (false);
	}
	return (true);
}

void	execute_pipeline(t_cmd *cmd, t_lst_cmd *head)
{
	int			prev_fd[2];
	t_cmd		*tmp;
	pid_t		pids[PID_MAX];
	int			count;
	t_fork_info	info;

	prev_fd[0] = -1;
	prev_fd[1] = -1;
	tmp = cmd;
	count = 0;
	info.pids = pids;
	info.count = &count;
	if (!validate_pipeline(cmd))
		return ;
	while (tmp)
	{
		fork_and_execute(tmp, prev_fd, head, &info);
		tmp = tmp->next;
	}
	handle_signals();
	wait_for_pipeline(info.pids, count);
	g_shell.child_running = 0;
}
