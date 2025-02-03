/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:13 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/03 13:11:42 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipes(char *cmd, char **envp)
{
	int		i;
	char	**splitted;
	char	*tmp;

	splitted = ft_split(cmd, "|");
	i = -1;
	while (splitted[++i])
	{
		tmp = ft_strtrim(splitted[i], " ");
		free(splitted[i]);
		splitted[i] = tmp;
	}
	i = -1;
	while (splitted[++i])
		child_pipe(splitted[i], envp, splitted[i + 1] == NULL);
	free_split(splitted);
}

static char	*get_env(char **envp, char *cmd)
{
	char	*tmp;
	size_t	len;
	int		i;

	i = 0;
	tmp = ft_strjoin(cmd + 1, "=");
	len = ft_strlen(tmp);
	while (envp[i] && ft_strnstr(envp[i], tmp, len) == 0)
		i++;
	free(tmp);
	if (envp[i])
		return (envp[i] + len);
	return ("");
}

void	handle_hear_doc(char *limiter)
{
	pid_t	line_reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		error(1, "Error with pipe creation!");
	line_reader = fork();
	if (line_reader == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = readline(">");
			if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

static void	check_redirections(char **splitted, int i)
{
	if (!ft_strncmp(splitted[i], "<", 2) && splitted[i + 1])
		reassemble_split(splitted, i, 0);
	else if (!ft_strncmp(splitted[i], ">", 2) && splitted[i + 1])
		reassemble_split(splitted, i, 1);
	else if (!ft_strncmp(splitted[i], ">>", 3) && splitted[i + 1])
		reassemble_split(splitted, i, 2);
	else if (!ft_strncmp(splitted[i], "<<", 3) && splitted[i + 1])
	{
		handle_hear_doc(splitted[i + 1]);
		free(splitted[i]);
		free(splitted[i + 1]);
		splitted[i] = 0;
		splitted[i + 1] = 0;
		while (splitted[i + 2])
		{
			splitted[i] = ft_strdup(splitted[i + 2]);
			free(splitted[i + 2]);
			splitted[i + 2] = 0;
			i++;
		}
	}
}

char	**handle_special(char **splitted, char **envp)
{
	char	*env;
	int		i;

	i = -1;
	while (splitted[++i])
	{
		if (ft_strchr(splitted[i], '$'))
		{
			env = get_env(envp, splitted[i]);
			if (!ft_strncmp(env, "", 1) && !ft_strncmp(splitted[i], "$", 2))
				continue ;
			free(splitted[i]);
			splitted[i] = ft_strdup(env);
		}
		check_redirections(splitted, i);
	}
	return (splitted);
}
