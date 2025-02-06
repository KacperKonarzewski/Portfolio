/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:49:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/05 19:32:30 by kkonarze         ###   ########.fr       */
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

void	error(int i, char *str, int error_code);
void	use_cmd(char *cmd, t_env_var *envp, int *status);
int		file_opener(char *argv, int i);
void	manage_pipes(char *cmd, t_env_var *envp, int *status);
void	free_split(char **splited_str);
void	child(char *cmd, t_env_var *envp, int *status);
void	child_pipe(char *cmd, t_env_var *envp, int is_last, int *status);
char	*get_env_var(t_env_var *head, const char *key);
int		handle_text(char **text, t_env_var *envp, int *status);
void	handle_special(char **splitted, t_env_var *envp, int type, int *status);
int		reassemble_split(char **splitted, int i, int type);
void	signal_handler(int sig);
int		ft_pwd(void);
int		ft_cd(char *text);
int		ft_echo(char **text, t_env_var *envp, int *status);
int		get_input(char **line);
int		check_redirections(char **splitted, int i);
void	envp_to_list(t_env_var **head, char **envp);
int		print_env_vars(t_env_var *current);
void	free_env_list(t_env_var **head);
void	set_env_var(t_env_var **head, const char *key, const char *value);
char	**build_env_array(t_env_var **head);
void	unset_env_var(t_env_var **head, const char *key);
char	**ft_split_quotes(char *str, char *charset);

#endif
