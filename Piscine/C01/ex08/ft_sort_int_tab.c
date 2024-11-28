/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:42:34 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/26 02:55:32 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, int size)
{
	int	swapped;
	int	i;
	int	tmp;

	swapped = 1;
	while (swapped != 0)
	{
		i = 1;
		swapped = 0;
		while (i < size)
		{
			if (tab[i - 1] > tab[i])
			{
				tmp = tab[i - 1];
				tab[i - 1] = tab[i];
				tab[i] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}
