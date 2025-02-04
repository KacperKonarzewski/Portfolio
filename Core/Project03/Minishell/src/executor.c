/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:32:54 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/04 23:32:00 by kkonarze         ###   ########.fr       */
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

char	**build_env_array(t_env_var **head)
{
	t_env_var	*current;
	int			count;
	char		**envp;
	char		*entry;
	int			i;

	current = *head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	envp = malloc((count + 1) * sizeof(char *));
	current = *head;
	i = -1;
	while (++i < count)
	{
		entry = malloc(ft_strlen(current->key) + ft_strlen(current->value) + 2);
		sprintf(entry, "%s=%s", current->key, current->value);
		envp[i] = entry;
		current = current->next;
	}
	envp[count] = NULL;
	return (envp);
}

void	use_cmd(char *cmd, t_env_var *envp)
{
	char	**flag;
	char	*path;
	char	**converted;

	flag = ft_split(cmd, " ");
	if (handle_text(flag, envp))
	{
		free_split(flag);
		exit(EXIT_SUCCESS);
	}
	handle_special(flag, envp, 1);
	converted = build_env_array(&envp);
	path = get_path(converted, flag[0]);
	if (!path && try_exec(flag, converted))
		error(0, "Command not found!\n");
	if (execve(path, flag, converted) == -1)
	{
		free_split(flag);
		free(path);
		free_split(converted);
		error(1, NULL);
	}
}

void	child(char *cmd, t_env_var *envp)
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

void	child_pipe(char *cmd, t_env_var *envp, int is_last)
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
