/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:10:18 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/03 01:56:10 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_subtraction(int nb, int subtraction, int i)
{
	if (nb - subtraction > 0)
		i = check_subtraction(nb - subtraction, subtraction + 2, i + 1);
	else if (nb - subtraction == 0)
		return (i);
	else
		return (0);
	return (i);
}

int	ft_sqrt(int nb)
{
	if (nb < 0)
		return (0);
	return (check_subtraction(nb, 1, 1));
}
