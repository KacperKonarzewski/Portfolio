/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 01:42:35 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/24 01:56:01 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_rev_int_tab(int *tab, int size)
{
	int	i;
	int	tmp;
	int	tmp2;

	tmp = size;
	i = 0;
	size = size / 2;
	tmp--;
	while (i < size)
	{
		tmp2 = tab[i];
		tab[i] = tab[tmp - i];
		tab[tmp - i] = tmp2;
		i++;
	}
}
