/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filereader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:37:38 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/08 02:04:21 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	open_dict(int *fds, int argc, char **argv)
{
	if (argc == 3)
	{
		fds[0] = open(argv[1], O_RDONLY);
		fds[1] = open(argv[1], O_RDONLY);
	}
	else
	{
		fds[0] = open("numbers.dict", O_RDONLY);
		fds[1] = open("numbers.dict", O_RDONLY);
	}
}

void	close_dict(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}
