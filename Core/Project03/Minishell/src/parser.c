/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:13 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/05 10:20:09 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipes(char *cmd, t_env_var *envp, int *status)
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
		child_pipe(splitted[i], envp, splitted[i + 1] == NULL, status);
	free_split(splitted);
}

void	handle_hear_doc(char *limiter)
{
	pid_t	line_reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		error(1, NULL, 1);
	line_reader = fork();
	if (line_reader == 0)
	{
		close(fd[0]);
		while (get_input(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

int	check_redirections(char **splitted, int i)
{
	if (!ft_strncmp(splitted[i], "<", 2) && splitted[i + 1])
		return (reassemble_split(splitted, i, 0));
	if (!ft_strncmp(splitted[i], ">", 2) && splitted[i + 1])
		return (reassemble_split(splitted, i, 1));
	if (!ft_strncmp(splitted[i], ">>", 3) && splitted[i + 1])
		return (reassemble_split(splitted, i, 2));
	if (!ft_strncmp(splitted[i], "<<", 3) && splitted[i + 1])
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
		return (1);
	}
	return (0);
}

static int	handle_code(char **splitted, int i, int *status)
{
	//int		j;
	//int		count;
	//char	*trimmed;

	//j = -1;
	//count = 0;
	//if (ft_strchr(splitted[i], '\''))
	//	return (1);
	//while (splitted[i][++j])
	//	if (splitted[i][j] == '\"')
	//		count++;
	//if (count && count % 2)
	//	return (1);
	//trimmed = ft_strtrim(splitted[i], "\"");
	//free(splitted[i]);
	//splitted[i] = trimmed;
	if (!ft_strncmp(splitted[i], "$?", 3))
		return (free(splitted[i]), splitted[i] = ft_itoa(*status), 1);
	return (0);
}

void	handle_special(char **splitted, t_env_var *envp, int type, int *status)
{
	char	*env;
	int		i;

	i = -1;
	while (splitted[++i])
	{
		if (ft_strchr(splitted[i], '$') && ft_strncmp(splitted[i], "$", 2))
		{
			if (handle_code(splitted, i, status))
				continue ;
			env = get_env_var(envp, splitted[i] + 1);
			if (!env)
			{
				free(splitted[i]);
				splitted[i] = ft_strdup("");
				continue ;
			}
			free(splitted[i]);
			splitted[i] = ft_strdup(env);
		}
		if (type && check_redirections(splitted, i))
			if (splitted[i--] == 0)
				break ;
	}
}
