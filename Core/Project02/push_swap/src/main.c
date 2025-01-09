/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:52:59 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/09 11:44:13 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	print_stacks(t_stacks *stacks)
{
	size_t		i;

	i = 0;
	ft_printf("-----------------------\n");
	while (i < stacks->size_a || i < stacks->size_b)
	{
		if (i < stacks->size_a)
			ft_printf("%-3d ", stacks->st_a[i]);
		else
			ft_printf("    ");
		if (i < stacks->size_b)
			ft_printf("%-3d\n", stacks->st_b[i]);
		else
			ft_printf("\n");
		i++;
	}
	ft_printf("-   -\nA   B\n");
}

t_stacks	init_stacks(int argc, char **argv)
{
	t_stacks	stacks;

	stacks.st_a = malloc((argc - 1) * sizeof(int));
	stacks.st_b = malloc((argc - 1) * sizeof(int));
	stacks.cost = malloc((argc - 1) * sizeof(int));
	if (!stacks.st_a || !stacks.st_b || !stacks.cost)
	{
		ft_printf("Malloc problem.");
		exit(EXIT_SUCCESS);
	}
	stacks.size_a = argc - 1;
	stacks.size_b = 0;
	while (--argc >= 1)
	{
		stacks.st_a[argc - 1] = ft_atoi(argv[argc]);
	}
	return (stacks);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (argc == 1)
		return (0);
	stacks = init_stacks(argc, argv);
	push_swap(&stacks);
	print_stacks(&stacks);
	return (0);
}
