/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:58:35 by feedback          #+#    #+#             */
/*   Updated: 2025/07/17 13:12:40 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_state	g_shell = {.exit_status = 0, .in_heredoc = 0,
	.child_running = 0};

int	check_tabs_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
		i++;
	if (input[i] == '\0')
		return (0);
	else
		return (1);
}

void	init_commands(t_lst_cmd *cmds, t_env *envir)
{
	t_cmd	*cmd;

	cmd = cmds->head;
	while (cmd)
	{
		cmd->env = &envir;
		cmd->envp = env_tochar(envir);
		cmd = cmd->next;
	}
	cmd = cmds->head;
	if (!cmd->next && is_builtin(cmd->args[0]))
		g_shell.exit_status = execute_builtin(cmd, cmds);
	else
	{
		g_shell.child_running = 1;
		execute_pipeline(cmd ,cmds);
		g_shell.child_running = 0;
	}
}

void	setup_shell_state(void)
{
	handle_signals();
	g_shell.child_running = 0;
}

void	exit_shell(void)
{
	write(1, "exit\n", 5);
	exit(g_shell.exit_status);
}

void	shell_loop(t_env *envir)
{
	char		*input;
	t_lst_cmd	*cmds;
	
	while (1)
	{
		setup_shell_state();
		input = readline("minishell:$ ");
		if (!input)
			exit_shell();
		if (!check_tabs_spaces(input))
		{
			free(input);
			continue;
		}
		if (*input)
			add_history(input);
		cmds = parsing(input, envir, &g_shell.exit_status);
		free(input);
		if (!cmds || !cmds->head)
		{
			if (cmds)
			free_all(cmds->k);
			continue;
		}
		init_commands(cmds, envir);
		close_redirs(cmds->head->files);
		t_cmd *tmp;
		tmp = cmds->head;
		while(tmp)
		{
			free_array(tmp->envp);
			tmp = tmp->next;
		}
		free_all(cmds->k);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env *envir = get_env(envp);

	(void)argc;
	(void)argv;

	shell_loop(envir);
	free_env_list(envir);
	return (g_shell.exit_status);
}
