/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:49:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/03 14:43:31 by kkonarze         ###   ########.fr       */
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

void	error(int i, char *str);
void	use_cmd(char *cmd, char **envp);
int		file_opener(char *argv, int i);
void	manage_pipes(char *cmd, char **envp);
void	free_split(char **splited_str);
void	child(char *cmd, char **envp);
void	child_pipe(char *cmd, char **envp, int is_last);
char	**handle_special(char **splitted, char **envp);
void	reassemble_split(char **splitted, int i, int type);
void	signal_handler(int sig);

#endif
