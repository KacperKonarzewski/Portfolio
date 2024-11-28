/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:27:29 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/23 23:29:59 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_string(char *c, int length)
{
	write(1, c, length);
}

void	set_tmp(int *t, int s)
{
	if (s == 0)
	{
		*t = 1;
	}
	else
	{
		*t = (s % 10) + 1;
	}
}

void	ft_putnbr(int nb, int l, int r)
{
	char	c;

	if (nb / 10 != 0)
	{
		ft_putnbr(nb / 10, l, r + 1);
	}
	else
	{
		if (r == l - 1)
		{
			print_string("0", 1);
		}
	}
	c = '0' + (nb % 10);
	write(1, &c, 1);
}

void	write_comb(int s, int n, int f, int l)
{
	int	i;
	int	tmp;

	i = 0;
	if (n == 0)
	{
		if (f != 1)
		{
			print_string(", ", 2);
		}
		ft_putnbr(s, l, 1);
		return ;
	}
	set_tmp(&tmp, s);
	i = tmp;
	while (i < 10)
	{
		write_comb(s * 10 + i, n - 1, f, l);
		f = 0;
		i++;
	}
}

void	ft_print_combn(int n)
{
	int	i;
	int	first;

	i = 0;
	first = 1;
	while (i <= 10 - n)
	{
		if (i != 0)
		{
			first = 0;
		}
		write_comb(i, n - 1, first, n);
		i++;
	}
}
