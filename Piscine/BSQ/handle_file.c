/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:53:04 by dszafran          #+#    #+#             */
/*   Updated: 2024/09/11 03:07:57 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

void	open_file(char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
}

void	close_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

int	line_size(int fd)
{
	int		len;
	char	c;

	len = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		len++;
	}
	return (len);
}

void	create_fds(int *fds, char *filename, int flag)
{
	fds[0] = open(filename, O_RDONLY);
	fds[1] = open(filename, O_RDONLY);
	if (flag == 1)
	{
		line_size(fds[0]);
		line_size(fds[1]);
	}
}

int	get_len(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
