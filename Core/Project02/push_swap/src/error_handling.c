/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 20:57:40 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/11 21:51:04 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	throw_error(t_stacks *s)
{
	write(2, "Error\n", 6);
	if (s)
		free_stacks(s);
	exit(EXIT_FAILURE);
}

void	check_if_dup(t_stacks *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < s->size_a)
	{
		j = i + 1;
		while (j < s->size_a)
		{
			if (s->st_a[i] == s->st_a[j])
				throw_error(s);
			j++;
		}
		i++;
	}
}

void	check_if_illegal(const char *nptr, t_stacks *s)
{
	int	i;
	int	d;
	int sign;

	i = -1;
	while (nptr[++i])
		if (nptr[i] != '-' && nptr[i] != '+' && !ft_isdigit(nptr[i])
			&& (nptr[i] < 9 || nptr[i] > 13) && nptr[i] != ' ')
			throw_error(s);
	i = -1;
	d = 0;
	sign = 0;
	while (nptr[++i])
	{
		if (sign && (nptr[i] == '-' || nptr[i] == '+'))
			throw_error(s);
		else if (sign == 0 && (nptr[i] == '-' || nptr[i] == '+'))
			sign = 1;
		if (d && !ft_isdigit(nptr[i]))
			throw_error(s);
		else if (d == 0 && ft_isdigit(nptr[i]))
			d = 1;
	}
	if (d == 0)
		throw_error(s);
}

int	ps_atoi(const char *nptr, t_stacks *s)
{
	int	count;
	int	i;
	int	is_negative;

	i = 0;
	count = 0;
	is_negative = 1;
	check_if_illegal(nptr, s);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		is_negative = (nptr[i] == '+') - (nptr[i] == '-');
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		count = (count * 10) + ((nptr[i++] - 48) * is_negative);
		if (is_negative < 0 && count > 0)
			throw_error(s);
		else if (is_negative > 0 && count < 0)
			throw_error(s);
	}
	return (count);
}
