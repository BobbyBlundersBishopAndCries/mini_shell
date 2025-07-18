/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:58:35 by feedback          #+#    #+#             */
/*   Updated: 2025/07/18 05:54:50 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_state	g_shell = {.exit_status = 0, .in_heredoc = 0,
		.child_running = 0};

void	free_it(t_lst_cmd *cmd)
{
	t_cmd *(c);
	c = cmd->head;
	while (c)
	{
		free_array(c->envp);
		c = c->next;
	}
	free_all(cmd->k);
}

static bool	sh_loop_aid(t_env *envir, char *input)
{
	t_lst_cmd	*cmds;

	if (*input)
		add_history(input);
	cmds = parsing(input, envir);
	free(input);
	if (!cmds || !cmds->head)
	{
		if (cmds)
			free_all(cmds->k);
		return (true);
	}
	init_commands(cmds, envir);
	close_redirs(cmds->head->files);
	free_it(cmds);
	return (false);
}

void	shell_loop(t_env *envir)
{
	char *(input);
	while (1)
	{
		setup_shell_state();
		input = readline("minishell:$ ");
		if (!input)
		{
			free_env_list(envir);
			exit_shell();
		}
		if (!check_tabs_spaces(input))
		{
			free(input);
			continue ;
		}
		if (sh_loop_aid(envir, input))
			continue ;
	}
	free_env_list(envir);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envir;

	(void)argc;
	(void)argv;
	envir = get_env(envp);
	shell_loop(envir);
	return (g_shell.exit_status);
}
