/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:31:49 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/06 23:18:28 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ra(t_stacks *stacks)
{
	size_t	i;
	int		tmp;

	if (stacks->size_a <= 1)
		return ;
	i = -1;
	tmp = stacks->stack_a[0];
	while (++i < stacks->size_a - 1)
		stacks->stack_a[i] = stacks->stack_a[i + 1];
	stacks->stack_a[i] = tmp;
}

void	rb(t_stacks *stacks)
{
	size_t	i;
	int		tmp;

	if (stacks->size_b <= 1)
		return ;
	i = -1;
	tmp = stacks->stack_b[0];
	while (++i < stacks->size_b - 1)
		stacks->stack_b[i] = stacks->stack_b[i + 1];
	stacks->stack_b[i] = tmp;
}

void	rr(t_stacks *stacks)
{
	ra(stacks);
	rb(stacks);
}
