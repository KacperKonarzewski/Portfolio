/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:26:12 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/12 08:53:08 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int i, char *str, int error_code)
{
	if (i)
	{
		perror("Error");
		exit(errno);
	}
	else
	{
		printf("%s", str);
		exit(error_code);
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

static int	file_opener(char **file, int i, t_env_var *envp)
{
	int		fd;
	char	*key;

	if (ft_strchr(*file, '$'))
	{
		key = extract_key(*file);
		find_key(file, key, 0, envp);
	}
	if (!i)
		fd = open(*file, O_RDONLY, 0777);
	else if (i == 1)
		fd = open(*file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(*file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		error(1, NULL, 0);
	return (fd);
}

int	reassemble_split(char **splitted, int i, int type, t_env_var *envp)
{
	int		fd;
	char	*trimmed;

	trimmed = ft_strtrim(splitted[i + 1], " ");
	free(splitted[i + 1]);
	splitted[i + 1] = trimmed;
	fd = file_opener(&splitted[i + 1], type, envp);
	if (type == 0)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	free(splitted[i + 1]);
	free(splitted[i]);
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

int	get_input(char **line)
{
	char	*buffer;
	char	c;
	int		bytes_read;
	int		i;

	i = 0;
	bytes_read = 0;
	buffer = (char *)malloc(1000);
	if (!buffer)
		return (-1);
	write(0, ">", 1);
	bytes_read = read(0, &c, 1);
	while (bytes_read && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		bytes_read = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = ft_strdup(buffer);
	free(buffer);
	return (bytes_read);
}
