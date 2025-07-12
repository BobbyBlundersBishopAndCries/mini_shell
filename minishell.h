/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:38:27 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/11 13:43:46 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ─────────────────────────────────────────────────────────── */
/*                        INCLUDE LIBRARIES                    */
/* ─────────────────────────────────────────────────────────── */

# include "libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# define READ_END 0
# define WRITE_END 1

typedef struct s_shell_state
{
	int					exit_status;
	int					sigint_received;
	int					in_heredoc;
	int 				child_running;
}						t_shell_state;
extern t_shell_state	g_shell;

/* ─────────────────────────────────────────────────────────── */
/*                       MEMORY MANAGER (GC)                   */
/* ─────────────────────────────────────────────────────────── */

typedef struct s_housekept
{
	void				*addrs;
	struct s_housekept	*next;
}						t_housekept;

typedef struct s_lst_hk
{
	t_housekept			*head;
}						t_lst_hk;

/* ─────────────────────────────────────────────────────────── */
/*                      FINAL PARSED STRUCTURE                 */
/* ─────────────────────────────────────────────────────────── */

typedef enum e_redirct
{
	R_APPEND,
	R_OUT,
	R_IN,
	R_HEREDOC
}						t_redirct;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_redir
{
	char				*files;
	t_redirct			index;
	bool deja_quoted ;
	int					fd;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	char				**args;
	t_redir				*files;
	t_env				**env;
	char				**envp;
	int					fd[2];
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_lst_cmd
{
	t_cmd				*head;
	t_lst_hk			*k;
}						t_lst_cmd;

/* ─────────────────────────────────────────────────────────── */
/*                          TOKENIZER                          */
/* ─────────────────────────────────────────────────────────── */

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}						t_type;

typedef struct s_token
{
	char				*token;
	t_type				type;
	bool deja_quoted;
	struct s_token *next;
}						t_token;

typedef struct s_lst_token
{
	t_token				*head;
}						t_lst_token;

typedef struct s_help
{
	t_lst_token			*token;
	t_token				*new;
	t_token				*tail;
	int					i;
}						t_help;

t_lst_token				*tokenizer(char *string, t_lst_hk *x);
t_token					*get_pipe(int *position, t_lst_hk *x);
t_token					*get_redir_in_here(char *string, int *position,
							t_lst_hk *x);
t_token					*get_redir_out_append(char *string, int *position,
							t_lst_hk *x);
t_token					*get_random_wrd(char *string, int *position,
							t_lst_hk *x);

/* ─────────────────────────────────────────────────────────── */
/*                          EXPANDER                           */
/* ─────────────────────────────────────────────────────────── */

typedef struct s_exstrct
{
	char				*res;
	int					i;
	bool				in_s;
	bool				in_d;
	char				tmp[2];
}						t_exstrct;

char					*string_expander(char *str, t_lst_hk *x, t_type a,
							t_env *env, int g_es);
void					expander(t_lst_token *token, t_lst_hk *x, t_env *env,
							int g_es);
char					*ft_strdump(const char *s1, t_lst_hk *x);
char					*ft_join(const char *s1, const char *s2, t_lst_hk *x);
char					*change_value(char *key, size_t count, t_lst_hk *x,
							t_env *env);

/* ─────────────────────────────────────────────────────────── */
/*                        SYNTAX CHECKER                       */
/* ─────────────────────────────────────────────────────────── */

typedef struct s_helpq
{
	int					s;
	int					d;
	int					i;
	bool				in_s;
	bool				in_d;
}						t_helpq;

int						check_quote(char *string);
int						sequotes_handle(t_lst_token *token);
int						syntax_analyser(t_lst_token *token);
int						sepipe_o(t_lst_token *token);
int						seredir_handle(t_lst_token *token);
int						redir_error(char *token);
int						pipe_error(void);
int						newline_error(void);
bool					is_redir(t_token *a);

/* ─────────────────────────────────────────────────────────── */
/*                    MEMORY / HELPER UTILS                    */
/* ─────────────────────────────────────────────────────────── */

int						addadrs_back(void *addrs, t_lst_hk *list);
void					*ft_malloc(size_t size, t_lst_hk *k);
void					free_all(t_lst_hk *k);
void					append_string(char *dest, const char *src, size_t size);
bool					is_op(char c);
void					trim_space(char **input);
void					print_lst(t_lst_token *ltoken);

/* ─────────────────────────────────────────────────────────── */
/*                          PARSING                            */
/* ─────────────────────────────────────────────────────────── */

t_lst_cmd				*parsing(char *input, t_env *env, int *g_es);
t_redir					*add_in_file(t_token *redir, t_token *file,
							t_redir *head, t_lst_hk *x);
size_t					get_all_argscmd(t_token *token);
typedef struct s_get_cmd_init
{
	t_token				*token;
	t_cmd				*cmd;
	size_t				index;
	size_t				count;
}						t_get_cmd_init;
void					init_get_cmd(t_get_cmd_init *init, t_token **t,
							t_lst_hk *x, t_env *env);
t_cmd					*get_cmd(t_token **t, t_lst_hk *x, t_env *env);
typedef struct s_init_fill
{
	t_lst_cmd			*lst_cmds;
	t_token				*token;
	t_cmd				*cmd;
	t_cmd				*tail;
}						t_init_fill;
void					fill_struct_init(t_init_fill *init,
							t_lst_token *lst_token, t_lst_hk *x);
t_lst_cmd				*fill_struct(t_lst_token *lst_token, t_lst_hk *x,
							t_env *env);

/* ─────────────────────────────────────────────────────────── */
/*                          EXECUTION                          */
/* ─────────────────────────────────────────────────────────── */

/* utiles_simo */
int						addback_node(t_env **head, char *av);
void					free_env_list(t_env *head);
t_env					*get_env(char **env);
void					update_env_value(t_env *node, char *value);
/* cd_utils.c */
char					*get_value(t_env *env, char *key);
void					update_val(t_env *env, char *key, char *new_val);
t_env					*find_env_node(t_env *env, char *key);
char					*resolve_cd_target(t_cmd *cmd);
char					*cd_to_path(t_cmd *cmd, char *oldpwd);
int						arg_count(char **av);
void					swap_env_nodes(t_env *a, t_env *b);
void					sort_list(t_env *head);
/**/
int						is_valid_identifier(char *name);
int						is_builtin(char *cmd);
void					free_array(char **array);
char					*strjoin_val_path(char *s1, char *s2, int flag);
char					**env_tochar(t_env *env);

/* builtins */
int						ft_cd(t_cmd *cmd);
int						ft_env(t_cmd *cmd);
int						ft_pwd(void);
int						ft_exit(t_cmd *cmd);
int						ft_echo(t_cmd *cmd);
int						ft_export(t_cmd *cmd);
int						ft_unset(t_cmd *cmd);
/* redtrections */
int						open_file(t_redir *redir, t_redirct mode);
int						redirect_fd(int fd, int std_fd);
int						setup_redirections(t_redir *list);
int						handle_all_heredocs(t_cmd *cmd);
int						handle_heredoc(t_redir *redir, t_env *env);
void					close_redirs(t_redir *list);
/* execute command */
int						exec_error_status(int err);
int						execute_builtin(t_cmd *cmd);
void					error(void);
void					execute_command(t_cmd *cmd);
void					execute_pipeline(t_cmd *cmd);
/* signals */
void					handle_signals(void);
void					sigint_handler(int signo);
void					restore_signals_to_default(void);
// export utils

#endif
