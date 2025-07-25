CC     = cc
CFLAGS = -Wall -Werror -Wextra  -g
LDFLAGS = -lreadline 

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

SRCS = main.c \
			main_utiles.c \
			exec/expand_heredoc.c \
			utiles_lkhdr/track_alloc_free.c \
			utiles_lkhdr/tools.c \
			parsing/parsing.c\
			lexical_analyser/main_token.c \
			syntax_analyser/syntax_analyser.c \
			expanding_variables/expander.c  \
			lexical_analyser/tokenizer_helper.c \
			syntax_analyser/sa_helper.c \
			expanding_variables/expander_helper.c \
			expanding_variables/utiles_2.c \
			expanding_variables/utiles.c \
			fin_parse/filling.c \
			fin_parse/filling_helper.c \
			utiles_simo/get_env.c \
			utiles_simo/free_list.c \
			utiles_simo/cd_utils.c\
			utiles_simo/export_utils.c \
			utiles_simo/env_tochar.c\
			utiles_simo/errno.c\
			utiles_simo/export_snd.c \
			builtins/ft_cd.c \
			builtins/ft_env.c \
			builtins/ft_pwd.c \
			builtins/ft_exit.c \
			builtins/ft_echo.c \
			builtins/ft_export.c \
			builtins/ft_unset.c \
			exec/execute_builtin.c \
			exec/execute_command.c \
			exec/red.c \
			exec/ex_helpheredoc.c \
			exec/fork_process.c\
			exec/here_doc_utils.c \
			exec/here_doc.c\
			exec/signal.c \
			exec/execute_pipeline.c
			
OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
