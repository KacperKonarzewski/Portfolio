/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utills.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:32:54 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/04 23:35:52 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int i, char *str)
{
	if (i)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_printf(str);
		exit(EXIT_SUCCESS);
	}
}

static void	free_split(char **splited_str)
{
	int	i;

	i = -1;
	while (splited_str[++i])
		free(splited_str[i]);
	free(splited_str);
}

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

int	file_opener(char *argv, int i)
{
	int	fd;

	if (!i)
		fd = open(argv, O_RDONLY, 0777);
	else if (i == 1)
		fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		error(1, "");
	return (fd);
}

void	use_cmd(char *cmd, char **envp)
{
	char	**flag;
	char	*path;

	flag = ft_split(cmd, " ");
	path = get_path(envp, flag[0]);
	if (!path)
	{
		free_split(flag);
		error(0, "No correct path found!");
	}
	if (execve(path, flag, envp) == -1)
	{
		free_split(flag);
		free(path);
		error(1, "");
	}
	free_split(flag);
	free(path);
}
