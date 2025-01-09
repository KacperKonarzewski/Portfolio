/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:31:49 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/09 14:29:36 by kkonarze         ###   ########.fr       */
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
	tmp = stacks->st_a[0];
	while (++i < stacks->size_a - 1)
		stacks->st_a[i] = stacks->st_a[i + 1];
	stacks->st_a[i] = tmp;
}

void	rb(t_stacks *stacks)
{
	size_t	i;
	int		tmp;

	if (stacks->size_b <= 1)
		return ;
	i = -1;
	tmp = stacks->st_b[0];
	while (++i < stacks->size_b - 1)
		stacks->st_b[i] = stacks->st_b[i + 1];
	stacks->st_b[i] = tmp;
}

void	rr(t_stacks *stacks)
{
	ra(stacks);
	rb(stacks);
}
