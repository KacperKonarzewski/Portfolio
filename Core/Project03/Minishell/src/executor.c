/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:32:54 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/12 09:55:47 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **envp, char *cmd)
{
	char	**poss_paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	poss_paths = ft_split(envp[i] + 5, ":");
	i = -1;
	while (poss_paths[++i])
	{
		part_path = ft_strjoin(poss_paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_split(poss_paths), path);
		free(path);
	}
	i = -1;
	free_split(poss_paths);
	return (NULL);
}

int	try_exec(char **flag, char **envp)
{
	char	*path;

	path = ft_strdup(flag[0]);
	if (execve(path, flag, envp) == -1)
	{
		free_split(flag);
		free(path);
		free_split(envp);
		return (1);
	}
	return (0);
}

void	use_cmd(char *cmd, t_env_var *envp, int *status)
{
	char	**flag;
	char	*path;
	char	*command;
	char	**converted;

	flag = ft_split_quotes(cmd, " ");
	command = ft_strtrim(flag[0], " ");
	if (flag[0])
		free(flag[0]);
	flag[0] = command;
	if (handle_text(flag, envp, status))
		exit(EXIT_SUCCESS);
	handle_special(flag + 1, envp, 1, status);
	converted = build_env_array(&envp);
	path = get_path(converted, flag[0]);
	if (!path && try_exec(flag, converted))
		error(0, "Command not found!\n", 127);
	if (execve(path, flag, converted) == -1)
	{
		free_split(flag);
		free(path);
		free_split(converted);
		error(1, NULL, 0);
	}
}

void	child(char *cmd, t_env_var *envp, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(1, NULL, 1);
	if (pid == 0)
		use_cmd(cmd, envp, status);
	waitpid(pid, status, 0);
	*status = (WIFEXITED(*status) != 0) * WEXITSTATUS(*status) \
			+ (WIFEXITED(*status) == 0) * 1;
}

void	child_pipe(char *cmd, t_env_var *envp, int is_last, int *status)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error(1, NULL, 1);
	pid = fork();
	if (pid == -1)
		error(1, NULL, 1);
	if (pid == 0)
	{
		if (!is_last)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		use_cmd(cmd, envp, status);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	if (!is_last)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, status, 0);
	*status = (WIFEXITED(*status) != 0) * WEXITSTATUS(*status) \
			+ (WIFEXITED(*status) == 0) * 1;
}
