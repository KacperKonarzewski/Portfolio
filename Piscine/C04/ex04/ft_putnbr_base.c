/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:50 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/02 20:08:29 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	get_len(char *base, int i)
{
	while (base[i])
		i++;
	return (i);
}

int	check_valid_base(char *base, int i, int j)
{
	while (base[++i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		j = i;
		while (base[++j])
			if (base[i] == base[j])
				return (1);
	}
	return (0);
}

int	ft_abs(int nbr)
{
	if (nbr < 0)
		nbr = -nbr;
	return (nbr);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	baselength;

	if (check_valid_base(base, -1, 0))
		return ;
	baselength = get_len(base, 0);
	if (baselength <= 1)
		return ;
	if (nbr < 0)
		write(1, "-", 1);
	if (nbr / baselength != 0)
		ft_putnbr_base(ft_abs(nbr / baselength), base);
	write(1, &base[ft_abs(nbr % baselength)], 1);
}
