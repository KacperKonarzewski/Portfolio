/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:43:54 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/25 12:20:57 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	check_char(int i, int j, int x, int y)
{
	char	c;

	c = 'B';
	if (x == 1)
	{
		x++;
	}
	else if (y == 1)
	{
		y++;
	}
	if (i != 1 && i != y && j != 1 && j != x)
	{
		c = ' ';
	}
	else if ((i == 1 && j == 1) || (i == y && j == 1))
	{
		c = 'A';
	}
	else if ((i == 1 && j == x) || (i == y && j == x))
	{
		c = 'C';
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
