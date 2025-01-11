/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:52:59 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/11 21:38:39 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdio.h>

void	rotate_to_lowest(t_stacks *s)
{
	size_t	i;
	int		mv_a;
	size_t	index;

	i = 0;
	index = 0;
	while (++i < s->size_a)
		if (s->st_a[index] > s->st_a[i])
			index = i;
	if (index < (s->size_a + 1) / 2)
		mv_a = index;
	else
		mv_a = (s->size_a - index) * -1;
	if (mv_a > 0)
		while (mv_a--)
			ra(s, 0);
	else
		while (mv_a++)
			rra(s, 0);
}

t_stacks	init_stacks(int argc, char **argv)
{
	t_stacks	stacks;

	stacks.st_a = malloc((argc - 1) * sizeof(int));
	stacks.st_b = malloc((argc - 1) * sizeof(int));
	stacks.cost = malloc((argc - 1) * sizeof(int));
	stacks.target_b = malloc((argc - 1) * sizeof(size_t));
	if (!stacks.st_a || !stacks.st_b || !stacks.cost || !stacks.target_b)
	{
		ft_printf("Malloc problem.");
		exit(EXIT_SUCCESS);
	}
	stacks.size_a = argc - 1;
	stacks.size_b = 0;
	while (--argc >= 1)
		stacks.st_a[argc - 1] = ps_atoi(argv[argc], &stacks);
	check_if_dup(&stacks);
	return (stacks);
}

void	free_stacks(t_stacks *stacks)
{
	free(stacks->st_a);
	free(stacks->st_b);
	free(stacks->cost);
	free(stacks->target_b);
}

void	push_swap(t_stacks *s)
{
	size_t	target_index;

	pb(s);
	pb(s);
	while (s->size_a > 3)
		move_cheapest_element(s);
	sort_three(s);
	while (s->size_b > 0)
	{
		target_index = find_target_index(s->st_a, s->size_a, s->st_b[0]);
		if (target_index <= s->size_a / 2)
			while (target_index-- > 0)
				ra(s, 0);
		else
		{
			target_index = s->size_a - target_index;
			while (target_index-- > 0)
				rra(s, 0);
		}
		pa(s);
	}
	rotate_to_lowest(s);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	int			sorted;
	size_t		i;

	i = 1;
	sorted = 0;
	if (argc == 1)
		throw_error((void *)0);
	stacks = init_stacks(argc, argv);
	while (i < stacks.size_a && stacks.st_a[i] > stacks.st_a[i - 1])
		i++;
	if (i == stacks.size_a)
		sorted = 1;
	if (!sorted)
	{
		if (stacks.size_a > 3)
			push_swap(&stacks);
		else if (stacks.size_a == 3)
			sort_three(&stacks);
		else if (stacks.size_a == 2)
			if (stacks.st_a[0] > stacks.st_a[1])
				ra(&stacks, 0);
	}
	free_stacks(&stacks);
	return (0);
}
