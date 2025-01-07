/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheapest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:03:45 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/07 22:51:35 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	move_cheapest_element(t_stacks *stacks)
{
	
}

void	push_swap(t_stacks *stacks)
{
	pb(stacks);
	pb(stacks);
	while (stacks->size_a > 3)
		move_cheapest_element(stacks);
}
