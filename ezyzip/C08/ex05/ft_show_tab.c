/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:20:30 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/12 01:27:06 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
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
		tmp = nb / 10;
		ft_putnbr(intabs(tmp));
	}
	c = '0' + intabs(nb % 10);
	write(1, &c, 1);
}

void	ft_print(char *str, int i)
{
	while (str[++i])
		write(1, &str[i], 1);
	write(1, "\n", 1);
}

void	ft_show_tab(struct s_stock_str *par)
{
	int	i;

	i = -1;
	while (par[++i].str != 0)
	{
		if (par[i].copy)
			ft_print(par[i].str, -1);
		ft_putnbr(par[i].size);
		write(1, "\n", 1);
		if (par[i].copy)
			ft_print(par[i].copy, -1);
	}
}
