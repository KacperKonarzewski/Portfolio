/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 06:08:17 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/12 06:18:31 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	c;

	c = 0;
	fd = 0;
	if (argc < 2)
		write(1, "File name missing.\n", 19);
	else if (argc > 2)
		write(1, "Too many arguments.\n", 20);
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			write(1, "Cannot read file.\n", 18);
			return (0);
		}
		while (read(fd, &c, 1) > 0)
			write(1, &c, 1);
	}
	close(fd);
	return (0);
}
