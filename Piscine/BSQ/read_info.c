/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:59:56 by dszafran          #+#    #+#             */
/*   Updated: 2024/09/11 22:34:24 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	open_file(char *filename, int *fd);
void	create_fds(int *fds, char *filename, int flag);
void	close_fds(int *fds);
int		line_size(int fd);
int		free_line(char *first_line);

int	get_line_size(char *filename)
{
	int	fd;
	int	len;

	open_file(filename, &fd);
	if (fd == -1)
		return (0);
	len = line_size(fd);
	close(fd);
	return (len);
}

char	*get_info_line(char *filename)
{
	char	*first_line;
	char	c;
	int		i;
	int		fds[2];
	int		len;

	create_fds(&fds[0], filename, 0);
	if (fds[0] == -1 || fds[1] == -1)
		return (NULL);
	len = line_size(fds[0]);
	first_line = (char *)malloc(len + 1);
	if (len < 4 || !first_line)
	{
		free(first_line);
		return (NULL);
	}
	i = 0;
	while (read(fds[1], &c, 1) > 0 && c != '\n')
	{
		first_line[i] = c;
		i++;
	}
	first_line[i] = '\0';
	close_fds(fds);
	return (first_line);
}

int	free_it(char *first_line, char *arr)
{
	free(arr);
	free(first_line);
	return (1);
}

int	line_count(char *filename)
{
	int		i;
	int		sum;
	int		len;
	char	*first_line;

	first_line = get_info_line(filename);
	len = get_line_size(filename);
	if (!first_line || len < 1)
		if (free_line(first_line))
			return (0);
	i = -1;
	sum = 0;
	while (++i < len - 3)
	{
		if (first_line[i] < '0' || first_line[i] > '9')
			if (free_line(first_line))
				return (0);
		sum = sum * 10 + (first_line[i] - 48);
	}
	free(first_line);
	if (sum <= 0)
		return (0);
	return (sum);
}

char	*get_info(char *filename)
{
	char	*arr;
	char	*first_line;
	int		i;
	int		len;

	len = get_line_size(filename);
	if (len < 1)
		return (NULL);
	first_line = get_info_line(filename);
	arr = (char *)malloc(4);
	if (!arr || !first_line)
		if (free_it(first_line, arr))
			return (NULL);
	i = -1;
	while (++i < 3)
		arr[i] = first_line[len - 3 + i];
	arr[3] = '\0';
	free(first_line);
	if (arr[0] == arr[1] || arr[0] == arr[2] || arr[1] == arr[2])
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
