/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:05:48 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/13 14:15:38 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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
		stacks.st_a[argc - 1] = ps_atoi(argv[argc], &stacks, NULL);
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

int	execute_instruction(char *instr, t_stacks *s)
{
	if (ft_strncmp(instr, "sa", 3) == 0)
		sa(s, 2);
	else if (ft_strncmp(instr, "sb", 3) == 0)
		sb(s, 2);
	else if (ft_strncmp(instr, "ss", 3) == 0)
		ss(s, 2);
	else if (ft_strncmp(instr, "pa", 3) == 0)
		pa(s, 2);
	else if (ft_strncmp(instr, "pb", 3) == 0)
		pb(s, 2);
	else if (ft_strncmp(instr, "ra", 3) == 0)
		ra(s, 2);
	else if (ft_strncmp(instr, "rb", 3) == 0)
		rb(s, 2);
	else if (ft_strncmp(instr, "rr", 3) == 0)
		rr(s, 2);
	else if (ft_strncmp(instr, "rra", 4) == 0)
		rra(s, 2);
	else if (ft_strncmp(instr, "rrb", 4) == 0)
		rrb(s, 2);
	else if (ft_strncmp(instr, "rrr", 4) == 0)
		rrr(s, 2);
	else
		return (0);
	return (1);
}

void	check_if_sorted(t_stacks *s)
{
	size_t	i;

	i = 1;
	if (s->size_b != 0)
	{
		write(1, "KO\n", 3);
		return ;
	}
	while (i < s->size_a)
	{
		if (s->st_a[i - 1] > s->st_a[i])
		{
			write(1, "KO\n", 3);
			return ;
		}
		i++;
	}
	write(1, "OK\n", 3);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	char		*line;
	size_t		len;
	size_t		i;

	if (argc == 1)
		return (0);
	stacks = init_stacks(argc, argv);
	i = 0;
	while (get_standard_input(&line))
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!execute_instruction(line, &stacks))
		{
			free(line);
			throw_error(&stacks, NULL);
		}
		free(line);
	}
	check_if_sorted(&stacks);
	free_stacks(&stacks);
	return (0);
}
