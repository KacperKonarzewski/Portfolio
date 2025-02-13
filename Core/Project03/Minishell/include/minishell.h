/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:49:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:19:17 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <signal.h>
# include <stddef.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type
{
	CMD,
	AND,
	OR,
	GROUP
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	char			*command;
	struct s_ast	*left;
	struct s_ast	*right;
}		t_ast;

void	error(int i, char *str, int error_code);
void	use_cmd(char *cmd, t_env_var *envp, int *status);
void	manage_pipes(char *cmd, t_env_var *envp, int *status);
void	free_split(char **splited_str);
void	child(char *cmd, t_env_var *envp, int *status);
void	child_pipe(char *cmd, t_env_var *envp, int is_last, int *status);
char	*get_env_var(t_env_var *head, const char *key);
int		handle_text(char **text, t_env_var *envp, int *status);
void	handle_special(char ***splitted, t_env_var *envp, int type,
			int *status);
int		find_key(char **split, char *key, int *status, t_env_var *envp);
char	*extract_key(char *splitted);
void	handle_status(char **split, char *k, ptrdiff_t chars[2], int *stat);
void	handle_space(char **text, int type);
void	remove_quotes(char **text, int type);
int		reassemble_split(char **splitted, int i, int type, t_env_var *envp);
t_ast	*ft_parse_expression(t_token **tokens);
void	signal_handler(int sig);
int		ft_pwd(void);
int		ft_cd(char *text, int *status);
int		ft_echo(char **text, t_env_var *envp, int *status);
int		get_input(char **line);
int		chck_redirc(char **splitted, int i, t_env_var *envp);
void	envp_to_list(t_env_var **head, char **envp);
int		print_env_vars(t_env_var *current);
void	free_env_list(t_env_var **head);
void	set_env_var(t_env_var **head, const char *key, const char *value);
char	**build_env_array(t_env_var **head);
void	unset_env_var(t_env_var **head, const char *key);
char	**ft_split_quotes(char *str, char *charset);
void	process_logical_operators(char *cmd, t_env_var *envp, int *status);
char	*expand_wildcards(char *pattern);
void	check_wildcards(char ***splitted, int i);
void	realloc_split(char ***splitted, char **expanded, int i);
char	*expand_wildcards(char *pattern);
t_ast	*handle_parenthesis(t_token **tokens);
t_ast	*handle_command(t_token **tokens);
t_ast	*ft_new_ast_node(t_node_type type, char *command);
t_token	*ft_tokenize(char *cmd);
void	ft_evaluate_ast(t_ast *node, t_env_var *envp, int *status);
void	ft_free_tokens(t_token *tokens);
void	ft_free_ast(t_ast *node);
char	*get_next_token(char **ptr);
void	skip_spaces(char **ptr);
void	ft_add_token(t_token **head, const char *value);

#endif
