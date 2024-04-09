/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:23:32 by yatabay           #+#    #+#             */
/*   Updated: 2023/10/20 18:32:45 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <asm/termbits.h>
# include <signal.h>
# include <string.h>
# include "libft/libft.h"
# include "time.h"

/*	shell signal modes	*/
# define INTERACTIVE 0
# define CHILD 1
# define HEREDOC 2
# define SLEEP 3

/*	idk	*/
# define MAX_ARGS 10

/*	redirection states	*/
# define OUT_TRUNC 1
# define OUT_APPEND 2
# define INPUT 3

/*	pipe ends	*/
# define READ_END 0
# define WRITE_END 1

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	int				infile;
	int				outfile;
	int				node_id;
	int				pipe_fd[2];
	pid_t			pid;
}				t_cmd;

typedef struct s_mini
{
	t_env	*env;
	t_list	*cmds;
}				t_mini;

/*	executing programs	*/
int		execute(t_mini *mini);
int		wait_child(t_mini *mini);
int		verify_path(char **path, t_cmd *node);

/*	builtins	*/
int		builtin_child_handler(t_cmd *node, t_env *env);
int		builtin_parent_handler(t_cmd *node, t_env *env);
void	mini_env(t_env *env, int outfile);
int		mini_export(t_cmd *node, t_env *env);
void	mini_unset(t_cmd *node, t_env *env);
void	update_pwd(t_env *env);
void	mini_dollarq(t_cmd *node);
int		execute_exit(t_cmd *node);
void	mini_cd_home(char *path, char *append, t_env *env);

/*	env functions	*/
t_env	*env_new(char *var);
void	env_add_back(t_env **env, char *var);
void	env_add_front(t_env **env, char *var);
int		env_length(t_env *env);
void	free_env(t_env *env);
t_env	*env_delete_first(t_env *env);
void	env_delete_last(t_env *env);
void	env_delete_middle(t_env *env, t_env *del);

/*	signal handlers	*/
void	signal_setup(int mode);
void	siginthandler(int sig);

/*	frees	*/
void	matrix_free(char **input);
void	free_and_clear(int nl_flag, t_env *env, char **input);
char	*free_dict(char *input, char *next);
int		search_free(char *search, char *to_free, int flag);

/*	misc	*/
char	*mini_getenv(char *name, t_env *env);

/*	input handling	*/
int		validate_input(char *input);
t_cmd	*init_cmd(void);
int		cmd_split_master(char *input, t_mini *mini);
int		quote(char *input, int i, char quote);
char	**cmd_pipe_split(char **cmd, int words);
char	**cmd_expand(char **cmd, t_env *env);
t_env	*find_var(t_env *env, char *var);
t_list	*cmd_save_list(char **cmd, t_env *env);
int		find_fd(int oldfd, char *cmd, int flag);
int		cmd_kill_quotes(char **cmd);
int		path_save_list(t_mini *mini);
int		alloc_words(char *input);
char	**cmd_split(char **cmd, char *input, int words);

/*	input helper	*/
int		check_for_exit(t_cmd *cmds, t_list *list);
t_cmd	*create_temp_cmd(t_list *temp);
char	*dup_and_free(char *todup, char **m1, char **m2, char **m3);

/*	list functions	*/
void	mini_list_add_back(t_cmd **new, char **cmd);
t_cmd	*mini_list_new(char **cmd);
void	print_list(t_mini *mini);

/*	heredoc	*/
int		find_heredoc_fd(char *delim, t_env *env);

/*	freees	*/
void	free_mini(t_mini *mini);

/*	helpers	*/
int		validate_pipes(char *str);
int		if_double_symbol(char **cmd, int i[]);
int		export_errors(t_cmd *node);
int		cmd_split_help(char *input, int i, int *j);
int		cmd_expand_filter(char **string, int *counters, char *exp, t_env *env);
int		cmd_find_var(char **cmd, char **exp, int *counter, t_env *env);
int		replace_var(char *var, char **cmd, int j, int k);
int		get_path_utils(char **path_check, t_cmd *node, int i);
int		check_str(char *str, char *temp);
int		cmd_kill_quotes_loop(char **cmd, char **str, int line, int end);
int		dfree(char **cmd, int *line, char *str);
int		check_str(char *str, char *temp);
int		fill_string(char **cmd, char **temp, int *i);
int		place_symbol(char *cmd, int *end, char**temp, int lines);
void	quote_skip(int character, char *string, int *increment, int *word);
char	*which_symbol(char *symbol, int *end, int flag);
char	*dup_or_join(char *first, char *second, char **to_free);
char	*create_temp(char **cmd, char *str, int line, int *end);
char	*join_and_free(char **str, char *temp);
char	*get_quote(char *cmd, int *end, char quote);
char	*no_quote(char *cmd, int *end);

#endif
