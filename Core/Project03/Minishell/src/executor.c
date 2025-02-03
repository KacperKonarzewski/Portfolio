/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:32:54 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/03 13:42:34 by kkonarze         ###   ########.fr       */
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
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	poss_paths = ft_split(envp[i] + 5, ":");
	i = -1;
	while (poss_paths[++i])
	{
		part_path = ft_strjoin(poss_paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_split(poss_paths);
			return (path);
		}
		free(path);
	}
	i = -1;
	free_split(poss_paths);
	return (NULL);
}

void	use_cmd(char *cmd, char **envp)
{
	char	**flag;
	char	*path;

	flag = ft_split(cmd, " ");
	handle_special(flag, envp);
	path = get_path(envp, flag[0]);
	if (!path)
	{
		free_split(flag);
		error(0, "Command not found!\n");
	}
	if (execve(path, flag, envp) == -1)
	{
		free_split(flag);
		free(path);
		error(1, NULL);
	}
	free_split(flag);
	free(path);
}

void	child(char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(1, "Fork failed");
	if (pid == 0)
	{
		use_cmd(cmd, envp);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, NULL, 0);
}

void	child_pipe(char *cmd, char **envp, int is_last)
{
	pid_t	pid;
	int		fd[2];

	if (!is_last && pipe(fd) == -1)
		error(1, "Pipe failed");
	pid = fork();
	if (pid == -1)
		error(1, "Fork failed");
	if (pid == 0)
	{
		if (!is_last)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		use_cmd(cmd, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (!is_last)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
}
