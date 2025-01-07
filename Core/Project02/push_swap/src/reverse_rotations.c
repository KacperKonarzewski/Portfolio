/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:07:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/06 23:18:42 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	rra(t_stacks *stacks)
{
	size_t	i;
	int		tmp;

	if (stacks->size_a <= 1)
		return ;
	i = stacks->size_a;
	tmp = stacks->stack_a[i - 1];
	while (--i >= 1)
		stacks->stack_a[i] = stacks->stack_a[i - 1];
	stacks->stack_a[0] = tmp;
}

void	rrb(t_stacks *stacks)
{
	size_t	i;
	int		tmp;

	if (stacks->size_b <= 1)
		return ;
	i = stacks->size_b;
	tmp = stacks->stack_b[i - 1];
	while (--i >= 1)
		stacks->stack_b[i] = stacks->stack_b[i - 1];
	stacks->stack_b[0] = tmp;
}

void	rrr(t_stacks *stacks)
{
	rra(stacks);
	rrb(stacks);
}
