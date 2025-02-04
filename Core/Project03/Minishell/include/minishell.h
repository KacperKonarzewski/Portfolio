/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:49:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/04 14:45:02 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
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

void	error(int i, char *str);
void	use_cmd(char *cmd, t_env_var *envp);
int		file_opener(char *argv, int i);
void	manage_pipes(char *cmd, t_env_var *envp);
void	free_split(char **splited_str);
void	child(char *cmd, t_env_var *envp);
void	child_pipe(char *cmd, t_env_var *envp, int is_last);
char	*get_env_var(t_env_var *head, const char *key);
int		handle_text(char **text, t_env_var *envp);
void	handle_special(char **splitted, t_env_var *envp);
int		reassemble_split(char **splitted, int i, int type);
void	signal_handler(int sig);
int		ft_pwd(void);
int		ft_cd(char *text);
int		ft_echo(char **text);
int		get_input(char **line);
int		check_redirections(char **splitted, int i);
void	envp_to_list(t_env_var **head, char **envp);
int		print_env_vars(t_env_var *current);

#endif
