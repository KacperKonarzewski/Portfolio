/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:14:01 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/13 20:48:15 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	count;
	int	i;
	int	is_negative;

	i = 0;
	count = 0;
	is_negative = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		is_negative = (nptr[i] == '+') - (nptr[i] == '-');
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
		count = (count * 10) + ((nptr[i++] - 48) * is_negative);
	return (count);
}
