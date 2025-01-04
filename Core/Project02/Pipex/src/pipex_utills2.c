/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utills2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:12:20 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/04 23:39:24 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
