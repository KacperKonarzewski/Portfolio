/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:43:54 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/25 12:01:28 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	check_char(int i, int j, int x, int y)
{
	char	c;

	c = 'o';
	if (i != 1 && i != y && j != 1 && j != x)
	{
		c = ' ';
	}
	else if ((i == 1 || i == y) && (j != 1 && j != x))
	{
		c = '-';
	}
	else if ((i != 1 && i != y) && (j == 1 || j == x))
	{
		c = '|';
	}
	ft_putchar(c);
}

void	rush(int x, int y)
{
	int	i;
	int	j;

	i = 1;
	while (i <= y)
	{
		j = 1;
		while (j <= x)
		{
			check_char(i, j, x, y);
			j++;
		}
		i++;
		ft_putchar('\n');
	}
}
