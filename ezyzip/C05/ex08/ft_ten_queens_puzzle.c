/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:21:09 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/03 22:43:35 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	print_sol(int board[10])
{
	int		i;
	char	c;

	i = -1;
	while (++i < 10)
	{
		c = '0' + board[i];
		write(1, &c, 1);
	}
	write(1, "\n", 1);
}

int	is_valid(int board[10][10], int row, int columns)
{
	int	i;
	int	j;

	i = -1;
	while (++i < columns)
		if (board[i][row] == 1)
			return (0);
	i = columns;
	j = row;
	while (--i >= 0 && --j >= 0)
		if (board[i][j] == 1)
			return (0);
	i = columns;
	j = row;
	while (--i >= 0 && ++j < 10)
		if (board[i][j] == 1)
			return (0);
	return (1);
}

int	solve_puzzle(int board[10][10], int columns, int poss[10])
{
	int	row;
	int	count;

	count = 0;
	if (columns == 10)
	{
		print_sol(poss);
		return (1);
	}
	row = -1;
	while (++row < 10)
	{
		if (is_valid(board, row, columns))
		{
			board[columns][row] = 1;
			poss[columns] = row;
			count += solve_puzzle(board, columns + 1, poss);
			board[columns][row] = 0;
		}
	}
	return (count);
}

int	ft_ten_queens_puzzle(void)
{
	int	board[10][10];
	int	poss[10];
	int	i;
	int	j;

	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			board[i][j] = 0;
	}
	i = -1;
	while (++i < 10)
	{
		poss[i] = 0;
	}
	return (solve_puzzle(board, 0, poss));
}
