/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:13 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 10:37:46 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipes(char *cmd, t_env_var *envp, int *status)
{
	int		i;
	int		stat;
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
	stat = 0;
	while (splitted[++i] && stat == 0)
	{
		child_pipe(splitted[i], envp, splitted[i + 1] == NULL, status);
		stat = *status;
	}
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
	free(limiter);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

int	chck_redirc(char **splitted, int i, t_env_var *envp)
{
	if (!ft_strncmp(splitted[i], "<", 2) && splitted[i + 1])
		return (reassemble_split(splitted, i, 0, envp));
	if (!ft_strncmp(splitted[i], ">", 2) && splitted[i + 1])
		return (reassemble_split(splitted, i, 1, envp));
	if (!ft_strncmp(splitted[i], ">>", 3) && splitted[i + 1])
		return (reassemble_split(splitted, i, 2, envp));
	if (!ft_strncmp(splitted[i], "<<", 3) && splitted[i + 1])
	{
		handle_hear_doc(ft_strtrim(splitted[i + 1], " "));
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

void	handle_status(char **split, char *k, ptrdiff_t chars[2], int *stat)
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

void	handle_special(char ***splitted, t_env_var *envp, int type, int *status)
{
	char	*key;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	while ((*splitted)[++(i[0])])
	{
		if (i[1] == 0)
			handle_space(&(*splitted)[i[0]], type);
		check_wildcards(splitted, i[0]);
		if (ft_strchr((*splitted)[i[0]], '$') && !ft_strnstr((*splitted)[i[0]] \
		, "$ ", ft_strlen((*splitted)[i[0]])) && (*splitted)[i[0]][0] != '\'')
		{
			i[1] = 1;
			key = extract_key((*splitted)[i[0]]);
			find_key(&(*splitted)[i[0]--], key, status, envp);
		}
		else
			i[1] = 0;
		if (type && chck_redirc((*splitted), i[0], envp) && (*splitted)[i[0]--] \
		== 0)
			break ;
		if (i[1] == 0)
			remove_quotes(&(*splitted)[i[0]], type);
	}
}
