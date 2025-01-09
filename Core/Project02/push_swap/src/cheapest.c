/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheapest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:03:45 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/09 14:31:18 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

//int	calc_cost(t_stacks *s, size_t index)
//{
//	int	moves_a;
//	int	moves_b;

//	moves_a = index % (s->size_a / 2) * (1 - (index < s->size_a / 2) * 2);
//	moves_b = 0;
//}

int	find_lowest(t_stacks *s)
{
	size_t	i;
	int		tmp;

	i = 0;
	tmp = -1;
	while (i < s->size_b)
		if (tmp > s->st_b[i++] || tmp == -1)
			tmp = s->st_b[i - 1];
	return (tmp);
}

int	find_highest(t_stacks *s)
{
	size_t	i;
	int		tmp;

	i = 0;
	tmp = -1;
	while (i < s->size_b)
		if (tmp < s->st_b[i++] || tmp == -1)
			tmp = s->st_b[i - 1];
	return (tmp);
}

void	find_target_b(t_stacks *s, size_t index)
{
	size_t	i;
	int		lowest;
	int		highest;

	i = 0;
	lowest = find_lowest(s);
	highest = find_highest(s);
	while (i < s->size_b - 1 && s->st_b[i] < s->st_a[index]
		&& (s->st_b[i] > s->st_b[i + 1] || s->st_a[index] < highest))
		i++;
	if (i + 1 == s->size_b && ((s->st_b[i] < s->st_a[index] && s->st_b[0] > \
	s->st_b[i]) || (s->st_b[i] > s->st_a[index] && s->st_b[0] < s->st_b[i])))
		i = 0;
	else if (s->st_b[i] < s->st_b[i + 1] && s->st_a[index] > highest)
		i++;
	else
	{
		while (i < s->size_b - 1 && s->st_a[index] < s->st_b[i]
			&& (s->st_b[i] > s->st_b[i + 1] || s->st_a[index] > lowest))
			i++;
		if (i + 1 == s->size_b && s->st_a[index] < s->st_b[i] && \
			s->st_b[i - 1] > s->st_b[i])
			i = 0;
	}
	s->target_b = i;
}

void	move_cheapest_element(t_stacks *stacks)
{
	find_target_b(stacks, 0);
	ft_printf("%d\n", stacks->st_b[stacks->target_b]);
}

void	push_swap(t_stacks *stacks)
{
	while (stacks->size_a > 1)
		pb(stacks);
	//while (stacks->size_a > 3)
		move_cheapest_element(stacks);
}
