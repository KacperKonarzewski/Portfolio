/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:06:13 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:09:20 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	gen_map(void)
{
	int	fd;
	int	x;
	int	y;
	int	tmp;

	x = rand() % 100 + 1;
	y = rand() % 100 + 1;
	fd = open("maps/random.fdf", O_WRONLY | O_TRUNC);
	if (fd < 0)
	{
		perror("Error");
		exit(-1);
	}
	while (y--)
	{
		tmp = x;
		while (tmp--)
		{
			ft_putnbr_fd((rand() % 8) * (1 - (rand() % 2 == 1) * 2), fd, 1);
			write(fd, " ", 1);
		}
		write(fd, "\n", 1);
	}
	close(fd);
}
