/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:32:58 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/12 19:33:25 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_putnbr_base(int nbr, char *base, int *i, char **str);

int	ft_error(char *base)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	while (base[len] != '\0')
		len++;
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
	return (len);
}

int	ft_find_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_basechange(char *str, char *base, int i)
{
	int	base_len;
	int	nb;
	int	pow;

	nb = 0;
	pow = 1;
	base_len = ft_error(base);
	if (base_len >= 2)
	{
		while (ft_find_in_base(str[i], base) != -1)
		{
			nb *= base_len;
			nb += ft_find_in_base(str[i], base);
			i++;
		}
		return (nb);
	}
	else
		return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	nb = ft_basechange(str, base, i);
	if (sign == -1)
		nb *= -1;
	return (nb);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		a;
	char	*str;

	a = 0;
	if (ft_error(base_from) == 0)
		return (NULL);
	if (ft_error(base_to) == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char));
	str[0] = '\0';
	return (ft_putnbr_base(ft_atoi_base(nbr, base_from), base_to, &a, &str));
}
