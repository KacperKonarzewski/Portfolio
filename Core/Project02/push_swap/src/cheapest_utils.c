/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheapest_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:39:56 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/12 22:09:36 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static size_t	find_lowest_b(t_stacks *s)
{
	size_t	i;
	int		tmp;
	size_t	index;

	i = 0;
	index = 0;
	tmp = s->st_b[i++];
	while (i < s->size_b)
	{
		if (tmp > s->st_b[i++])
		{
			tmp = s->st_b[i - 1];
			index = i - 1;
		}
	}
	return (index);
}

static size_t	find_highest_b(t_stacks *s)
{
	size_t	i;
	int		tmp;
	size_t	index;

	i = 0;
	tmp = s->st_b[i++];
	index = 0;
	while (i < s->size_b)
	{
		if (tmp < s->st_b[i++])
		{
			tmp = s->st_b[i - 1];
			index = i - 1;
		}
	}
	return (index);
}

void	find_target_b(t_stacks *s, size_t index)
{
	size_t	i;
	size_t	lowest;
	size_t	highest;

	i = 1;
	lowest = find_lowest_b(s);
	highest = find_highest_b(s);
	if (s->st_a[index] > s->st_b[highest])
	{
		s->target_b[index] = highest;
		return ;
	}
	if (s->st_a[index] < s->st_b[lowest])
	{
		s->target_b[index] = highest;
		return ;
	}
	while (i < s->size_b)
	{
		if (s->st_b[i] < s->st_a[index] && s->st_b[i - 1] > s->st_a[index])
			break ;
		i++;
	}
	s->target_b[index] = i;
}

void	rotate_both(t_stacks *s, int *mv_a, int *mv_b)
{
	if (*mv_b < 0 && *mv_a < 0)
	{
		while (*mv_b && *mv_a)
		{
			rrr(s, 1);
			(*mv_a)++;
			(*mv_b)++;
		}
	}
	else if (*mv_a > 0 && *mv_b > 0)
	{
		while (*mv_a && *mv_b)
		{
			rr(s, 1);
			(*mv_b)--;
			(*mv_a)--;
		}
	}
}

void	sort_three(t_stacks *s)
{
	int	first;
	int	second;
	int	third;

	first = s->st_a[0];
	second = s->st_a[1];
	third = s->st_a[2];
	if (first > second && second < third && first < third)
		sa(s, 0);
	else if (first > second && second > third)
	{
		sa(s, 0);
		rra(s, 0);
	}
	else if (first > second && second < third && first > third)
		ra(s, 0);
	else if (first < second && second > third && first < third)
	{
		sa(s, 0);
		ra(s, 0);
	}
	else if (first < second && second > third && first > third)
		rra(s, 0);
}
