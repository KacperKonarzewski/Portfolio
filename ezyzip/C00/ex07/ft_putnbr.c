/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:15:47 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/22 15:35:11 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	intabs(int i)
{
	if (i < 0)
	{
		i = i * -1;
	}
	return (i);
}

void	ft_putnbr(int nb)
{
	char	c;
	char	minus;
	int		tmp;

	minus = '-';
	if (nb < 0)
	{
		write(1, &minus, 1);
	}
	if (nb / 10 != 0)
	{
		ft_putnbr(nb / 10);
	}
	c = '0' + intabs(nb % 10);
	write(1, &c, 1);
}
