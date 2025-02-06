/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:13 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/06 14:29:39 by kkonarze         ###   ########.fr       */
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

static char	*extract_key(char *splitted, int *last)
{
	char	*key;
	int		start;
	int		end;
	int		i;

	start = *last;
	while (splitted[start] && splitted[start] != '$')
		start++;
	end = start + 1;
	while (!ft_isdigit(splitted[start + 1]) && \
		(ft_isalnum(splitted[end]) || splitted[end] == '_'))
		end++;
	end += (end == start + 1);
	key = malloc(sizeof(char) * (end - start + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (start + i++ < end)
		key[i - 1] = splitted[start + i - 1];
	key[end - start] = 0;
	//printf("%s\n%d\n%d\n", key, end, start);
	return (key);
}

int	find_key(char **splitted, char *key, int *status, t_env_var *envp)
{
	char		*env;
	char		*new_str;
	int			i;
	ptrdiff_t	dollar;

	(void)envp;
	dollar = ft_strchr(*splitted, '$') - *splitted;
	i = -1;
	if (!ft_strcmp(key, "$?"))
	{
		env = ft_itoa(*status);
		new_str = malloc(sizeof(char) * (ft_strlen(*splitted) + ft_strlen(env) - 1));
		if (!new_str)
			return (0);
		//printf("%s\n", env);
		while (++i < (int)dollar)
			new_str[i] = (*splitted)[i];
		while (i++ < (int)ft_strlen(env))
			new_str[i - 1] = env[i - 1 - (int)dollar];
		while (i++ < (int)ft_strlen(*splitted) + (int)ft_strlen(env) - 1)
			new_str[i - 1] = (*splitted)[i + 1];
		new_str[i] = 0;
		free(env);
		free(*splitted);
		*splitted = new_str;
		return (1);
	}
	return (0);
}
//
	//	return (free(splitted[i]), splitted[i] = ft_itoa(*status), 1);
	//

void	handle_special(char **splitted, t_env_var *envp, int type, int *status)
{
	char	*key;
	int		i;
	int		last;

	i = -1;
	while (splitted[++i])
	{
		if (ft_strchr(splitted[i], '$') && !ft_strnstr(splitted[i], "$ ", \
			ft_strlen(splitted[i])) && splitted[i][0] != '\'')
		{
			last = 0;
			key = extract_key(splitted[i], &last);
			if (find_key(&splitted[i], key, status, envp))
				i--;
		}
		if (type && check_redirections(splitted, i))
			if (splitted[i--] == 0)
				break ;
	}
}
