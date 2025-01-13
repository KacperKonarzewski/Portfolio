/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:56:25 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/13 14:14:08 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H

# define PUSHSWAP_H

# include "libft.h"

typedef struct s_stacks
{
	size_t	size_a;
	size_t	size_b;
	int		*st_a;
	int		*st_b;
	int		*cost;
	size_t	target_a;
	size_t	*target_b;
}		t_stacks;

void		push_swap(t_stacks *stacks);
void		move_cheapest_element(t_stacks *stacks);
void		free_split(char **split);
size_t		find_target_index(int *stack, size_t size, int value);
void		rotate_both(t_stacks *s, int *mv_a, int *mv_b);
void		find_target_b(t_stacks *s, size_t index);
void		sort_three(t_stacks *s);
void		free_stacks(t_stacks *stacks);
void		check_if_dup(t_stacks *s);
void		throw_error(t_stacks *s, char **split);
int			check_if_sorted(t_stacks *stacks);
t_stacks	init_stacks2(char **argv);
int			ps_atoi(const char *nptr, t_stacks *s, char **split);
void		sa(t_stacks *stacks, int ss);
void		sb(t_stacks *stacks, int ss);
void		ss(t_stacks *stacks, int type);
void		pa(t_stacks *stacks, int type);
void		pb(t_stacks *stacks, int type);
void		ra(t_stacks *stacks, int rr);
void		rb(t_stacks *stacks, int rr);
void		rr(t_stacks *stacks, int type);
void		rra(t_stacks *stacks, int rrr);
void		rrb(t_stacks *stacks, int rrr);
void		rrr(t_stacks *stacks, int type);

#endif
