/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:29 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/05 08:49:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_abs(int n)
{
	return (n * ((n > 0) - (n < 0)));
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;
	int		cpy;
	int		i;

	cpy = n;
	digits = 0;
	i = 0;
	while (cpy / 10 != 0)
	{
		digits += 1;
		cpy /= 10;
	}
	str = (char *)malloc(((n < 0) + digits + 2) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[(n < 0) + digits + 1] = 0;
	while (digits + (n < 0) >= (n < 0))
	{
		str[digits-- + (n < 0)] = ft_abs(n % 10) + 48;
		n /= 10;
	}
	return (str);
}
