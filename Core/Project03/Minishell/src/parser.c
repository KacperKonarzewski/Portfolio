/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:13 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/10 23:38:37 by kkonarze         ###   ########.fr       */
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
	char	*new_limiter;

	new_limiter = ft_strjoin(limiter, "\n");
	if (pipe(fd) == -1)
		error(1, NULL, 1);
	line_reader = fork();
	if (line_reader == 0)
	{
		close(fd[0]);
		while (get_input(&line))
		{
			if (ft_strncmp(line, new_limiter, ft_strlen(limiter) + 1) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	free(new_limiter);
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

static char	*extract_key(char *splitted)
{
	char	*key;
	int		start;
	int		end;
	int		i;

	start = 0;
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
	return (key);
}

static void	handle_status(char **split, char *k, ptrdiff_t chars[2], int *stat)
{
	char	*new_str;
	int		i;
	char	*code;
	int		code_len;
	size_t	key_len;

	code = ft_itoa(*stat);
	code_len = ft_strlen(code);
	key_len = ft_strlen(k);
	new_str = (char *)malloc(chars[0] + code_len + chars[1] + 1);
	if (!new_str)
		return ;
	i = -1;
	while (++i < (int)chars[0])
		new_str[i] = (*split)[i];
	i = -1;
	while (++i < (int)code_len)
		new_str[i + chars[0]] = code[i];
	i = -1;
	while (++i < (int)chars[1])
		new_str[i + chars[0] + code_len] = (*split)[i + chars[0] + key_len];
	new_str[chars[0] + code_len + chars[1]] = 0;
	free(*split);
	free(code);
	*split = new_str;
}

static void	redo_str(char **split, char *key, ptrdiff_t chars[2], int *status)
{
	char	*new_str;
	int		i;

	i = -1;
	if (!ft_strcmp(key, "$?"))
		handle_status(split, key, chars, status);
	else
	{
		new_str = (char *)malloc(chars[0] + chars[1] + 1);
		if (!new_str)
			return ;
		while (++i < (int)chars[0])
			new_str[i] = (*split)[i];
		i = -1;
		while (++i < (int)chars[1])
			new_str[i + chars[0]] = (*split)[chars[0] + ft_strlen(key) + i];
		new_str[chars[0] + chars[1]] = 0;
		free(*split);
		*split = new_str;
	}
}

int	find_key(char **split, char *key, int *status, t_env_var *envp)
{
	char		*env;
	char		*new_str;
	int			i;
	ptrdiff_t	chars[2];
	size_t		len;

	(void)status;
	chars[0] = ft_strnstr(*split, key, ft_strlen(*split)) - *split;
	chars[1] = (ptrdiff_t)(ft_strlen(*split) - ft_strlen(key)) - chars[0];
	env = get_env_var(envp, key + 1);
	if (!env)
		return (redo_str(split, key, chars, status), free(key), 0);
	i = -1;
	len = ft_strlen(env);
	new_str = (char *)malloc(chars[0] + len + chars[1] + 1);
	while (++i < (int)chars[0])
		new_str[i] = (*split)[i];
	while (i++ - (int)chars[0] < (int)len)
		new_str[i - 1] = env[i - 1 - (int)chars[0]];
	i = -1;
	while (++i < (int)chars[1])
		new_str[i + (int)len + (int)chars[0]] = (*split)[i + ft_strlen(key) \
		+ chars[0]];
	new_str[i + (int)len + (int)chars[0]] = 0;
	return (free(env), free(key), free(*split), *split = new_str, 1);
}

static void	handle_space(char **text)
{
	size_t	len;

	len = ft_strlen(*text);
	if (text[1] == 0)
		return ;
	if ((*text)[len - 1] != ' ')
		(*text)[len - 1] = 0;
}

static void	remove_quotes(char **text, int type)
{
	int		space[2];
	char	*joined[2];

	space[0] = 0;
	space[1] = 0;
	if ((*text)[ft_strlen((*text)) - 1] == ' ')
	{
		space[0] = 1;
		(*text)[ft_strlen(*text) - 1] = 0;
	}
	if ((*text)[0] == '\"' && ++(space[1]))
		joined[0] = ft_strtrim((*text), "\"");
	else if ((*text)[0] == '\'' && ++(space[1]))
		joined[0] = ft_strtrim((*text), "\'");
	if (space[1])
	{
		free((*text));
		(*text) = joined[0];
	}
	if (!type && space[0] && space[1])
	{
		joined[1] = ft_strjoin((*text), " ");
		free((*text));
		(*text) = joined[1];
	}
}

void	handle_special(char **splitted, t_env_var *envp, int type, int *status)
{
	char	*key;
	int		i;
	int		last;

	i = -1;
	last = 0;
	while (splitted[++i])
	{
		if (last == 0)
			handle_space(&splitted[i]);
		if (ft_strchr(splitted[i], '$') && !ft_strnstr(splitted[i], "$ ", \
			ft_strlen(splitted[i])) && splitted[i][0] != '\'')
		{
			last = 1;
			key = extract_key(splitted[i]);
			if (find_key(&splitted[i], key, status, envp))
				i--;
		}
		else
			last = 0;
		if (type && check_redirections(splitted, i) && splitted[i--] == 0)
			break ;
		if (last == 0)
			remove_quotes(&splitted[i], type);
	}
}
