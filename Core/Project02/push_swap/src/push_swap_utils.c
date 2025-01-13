/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:00:04 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/13 14:55:14 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

t_stacks	init_stacks2(char **argv)
{
	char		**split;
	t_stacks	stacks;
	size_t		len;
	size_t		i;

	split = ft_split(argv[1], " ");
	len = 0;
	i = 0;
	while (split[len])
		len++;
	stacks.st_a = malloc((len) * sizeof(int));
	stacks.st_b = malloc((len) * sizeof(int));
	stacks.cost = malloc((len) * sizeof(int));
	stacks.target_b = malloc((len) * sizeof(size_t));
	if (!stacks.st_a || !stacks.st_b || !stacks.cost || !stacks.target_b)
	{
		ft_printf("Malloc problem.");
		exit(EXIT_SUCCESS);
	}
	stacks.size_a = len;
	stacks.size_b = 0;
	while (i++ < len)
		stacks.st_a[i - 1] = ps_atoi(split[i - 1], &stacks, split);
	free_split(split);
	return (stacks);
}
