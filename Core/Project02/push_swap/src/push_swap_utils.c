/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:46:58 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/02 13:02:43 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	stack_size(t_stack *stack)
{
	int		i;

	i = 0;
	while (stack != NULL)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}

t_stack	*stack_new(int number)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->value = number;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	stack_add_front(t_stack **lst, t_stack *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->next = *lst;
		new->prev = NULL;
		(*lst)->prev = new;
		*lst = new;
	}
}

void	stack_add_back(t_stack **lst, t_stack *new)
{
	t_stack	*find_lst;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	find_lst = *lst;
	while (find_lst->next != NULL)
		find_lst = find_lst->next;
	new->prev = find_lst;
	find_lst->next = new;
}
