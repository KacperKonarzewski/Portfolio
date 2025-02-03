/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:26:12 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/03 13:02:07 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int i, char *str)
{
	if (i)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%s", str);
		exit(EXIT_SUCCESS);
	}
}

void	free_split(char **splited_str)
{
	int	i;

	i = -1;
	while (splited_str[++i])
		free(splited_str[i]);
	free(splited_str);
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
		error(1, NULL);
	return (fd);
}

void	reassemble_split(char **splitted, int i, int type)
{
	int	fd;

	fd = file_opener(splitted[i + 1], type);
	if (type == 0)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
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
