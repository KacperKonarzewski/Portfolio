/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_standard_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:41:22 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/12 23:47:05 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_read(char **line, int bytes_read, char *buffer)
{
	if (bytes_read <= 0)
	{
		free(buffer);
		*line = NULL;
		return (1);
	}
	return (0);
}

int	get_standard_input(char **line)
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
	bytes_read = read(0, &c, 1);
	if (check_read(line, bytes_read, buffer))
		return (bytes_read);
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
