/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:33:37 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/12 19:33:51 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_putchar(char c, int *index, char **str)
{
	char	*tmp;
	int		i;

	tmp = (char *)malloc(*index + 2);
	if (!tmp)
		return ;
	i = 0;
	while ((*str)[i] != '\0')
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i++] = c;
	tmp[i] = '\0';
	free(*str);
	*str = tmp;
	*index += 1;
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	checkerror(char *base)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(base);
	i = 0;
	if (base[0] == '\0' || len == 1)
		return (0);
	while (base[i] != '\0')
	{
		if (base[i] <= ' ' || base[i] == 127 || base[i] == '+'
			|| base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	*ft_putnbr_base(int nbr, char *base, int *i, char **str)
{
	int		len;
	long	nb;

	len = ft_strlen(base);
	nb = nbr;
	if (checkerror(base) == 1)
	{
		if (nb < 0)
		{
			ft_putchar('-', i, str);
			nb *= -1;
		}
		if (nb < len)
		{
			ft_putchar(base[nb], i, str);
		}
		if (nb >= len)
		{
			ft_putnbr_base(nb / len, base, i, str);
			ft_putnbr_base(nb % len, base, i, str);
		}
	}
	else
		*str = NULL;
	return (*str);
}
