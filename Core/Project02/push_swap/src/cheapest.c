/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheapest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:03:45 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/12 22:09:26 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdio.h>

int	ft_abs(int d)
{
	return (d * ((d > 0) - (d < 0)));
}

void	calc_cost(t_stacks *s, size_t index)
{
	int	mv_a;
	int	mv_b;
	int	cost;

	if (index < (s->size_a + 1) / 2)
		mv_a = index;
	else
		mv_a = (s->size_a - index) * -1;
	if (s->target_b[index] < (s->size_b + 1) / 2)
		mv_b = s->target_b[index];
	else
		mv_b = (s->size_b - s->target_b[index]) * -1;
	if (mv_a <= 0 && mv_b <= 0)
		cost = ft_abs((mv_a <= mv_b) * mv_a + (mv_b < mv_a) * mv_b);
	else if (mv_a >= 0 && mv_b >= 0)
		cost = (mv_a >= mv_b) * mv_a + (mv_b > mv_a) * mv_b;
	else if (mv_a > 0)
		cost = mv_a - mv_b;
	else
		cost = mv_b - mv_a;
	cost++;
	s->cost[index] = cost;
}

void	rotate(t_stacks *s)
{
	int	mv_b;
	int	mv_a;

	if (s->target_a < (s->size_a + 1) / 2)
		mv_a = s->target_a;
	else
		mv_a = (s->size_a - s->target_a) * -1;
	if (s->target_b[s->target_a] < (s->size_b + 1) / 2)
		mv_b = s->target_b[s->target_a];
	else
		mv_b = (s->size_b - s->target_b[s->target_a]) * -1;
	rotate_both(s, &mv_a, &mv_b);
	if (mv_a > 0)
		while (mv_a--)
			ra(s, 0);
	else
		while (mv_a++)
			rra(s, 0);
	if (mv_b > 0)
		while (mv_b--)
			rb(s, 0);
	else
		while (mv_b++)
			rrb(s, 0);
}

void	move_cheapest_element(t_stacks *stacks)
{
	ssize_t	i;
	int		tmp;

	i = 0;
	while ((size_t)i < stacks->size_a)
	{
		find_target_b(stacks, i);
		calc_cost(stacks, i);
		if (stacks->cost[i++] <= 2)
			break ;
	}
	tmp = stacks->cost[0];
	stacks->target_a = 0;
	while (--i >= 0)
	{
		if (tmp >= stacks->cost[i])
		{
			stacks->target_a = i;
			tmp = stacks->cost[i];
		}
	}
	rotate(stacks);
	pb(stacks, 1);
}

size_t	find_target_index(int *stack, size_t size, int value)
{
	size_t	prev;
	size_t	min_index;
	size_t	i;

	i = 0;
	while (i < size)
	{
		prev = (i - 1 + size) % size;
		if (stack[i] > value && stack[prev] < value)
			return (i);
		i++;
	}
	min_index = 0;
	i = 1;
	while (i < size)
	{
		if (stack[i] < stack[min_index])
			min_index = i;
		i++;
	}
	return (min_index);
}
