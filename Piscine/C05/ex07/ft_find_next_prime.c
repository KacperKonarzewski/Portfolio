/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 02:18:02 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/03 02:23:40 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	prime_recursion(int nb, int i)
{
	if (nb < 2)
		return (0);
	if (nb == 2)
		return (1);
	if (nb % i == 0)
		return (0);
	if (nb < i * i)
		return (1);
	return (prime_recursion(nb, i + 1));
}

int	ft_find_next_prime(int nb)
{
	while (prime_recursion(nb, 2) == 0)
		nb++;
	return (nb);
}
