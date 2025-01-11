/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:07:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/10 19:45:26 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	rra(t_stacks *stacks, int rrr)
{
	size_t	i;
	int		tmp;

	if (stacks->size_a <= 1)
		return ;
	i = stacks->size_a;
	tmp = stacks->st_a[i - 1];
	while (--i >= 1)
		stacks->st_a[i] = stacks->st_a[i - 1];
	stacks->st_a[0] = tmp;
	if (!rrr)
		ft_printf("rra\n");
}

void	rrb(t_stacks *stacks, int rrr)
{
	size_t	i;
	int		tmp;

	if (stacks->size_b <= 1)
		return ;
	i = stacks->size_b;
	tmp = stacks->st_b[i - 1];
	while (--i >= 1)
		stacks->st_b[i] = stacks->st_b[i - 1];
	stacks->st_b[0] = tmp;
	if (!rrr)
		ft_printf("rrb\n");
}

void	rrr(t_stacks *stacks)
{
	rra(stacks, 1);
	rrb(stacks, 1);
	ft_printf("rrr\n");
}
