/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 20:57:40 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/13 14:14:38 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	throw_error(t_stacks *s, char **split)
{
	write(2, "Error\n", 6);
	if (split)
		free_split(split);
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
				throw_error(s, NULL);
			j++;
		}
		i++;
	}
}

int	check_if_sorted(t_stacks *stacks)
{
	int		sorted;
	size_t	i;

	i = 0;
	sorted = 0;
	while (i < stacks->size_a && stacks->st_a[i] > stacks->st_a[i - 1])
		i++;
	if (i == stacks->size_a)
		sorted = 1;
	return (sorted);
}

void	check_if_illegal(const char *nptr, t_stacks *s, char **split)
{
	int	i;
	int	d;
	int	sign;

	i = -1;
	while (nptr[++i])
		if (nptr[i] != '-' && nptr[i] != '+' && !ft_isdigit(nptr[i])
			&& (nptr[i] < 9 || nptr[i] > 13) && nptr[i] != ' ')
			throw_error(s, split);
	i = -1;
	d = 0;
	sign = 0;
	while (nptr[++i])
	{
		if (sign && (nptr[i] == '-' || nptr[i] == '+'))
			throw_error(s, split);
		else if (sign == 0 && (nptr[i] == '-' || nptr[i] == '+'))
			sign = 1;
		if (d && !ft_isdigit(nptr[i]))
			throw_error(s, split);
		else if (d == 0 && ft_isdigit(nptr[i]))
			d = 1;
	}
	if (d == 0)
		throw_error(s, split);
}

int	ps_atoi(const char *nptr, t_stacks *s, char **split)
{
	int	count;
	int	i;
	int	is_negative;

	i = 0;
	count = 0;
	is_negative = 1;
	check_if_illegal(nptr, s, split);
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
			throw_error(s, split);
		else if (is_negative > 0 && count < 0)
			throw_error(s, split);
	}
	return (count);
}
