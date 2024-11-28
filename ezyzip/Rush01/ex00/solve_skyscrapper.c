/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_skyscrapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:55:27 by dszafran          #+#    #+#             */
/*   Updated: 2024/09/01 22:09:47 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	*add_to_row(int *arr, int *help_arr);
int	*add_to_col(int *arr, int *help_arr);
int	check_rows_left(int *poss, int size, int *povs);
int	check_rows_right(int *poss, int size, int *povs);
int	check_rows_top(int *poss, int size, int *povs);
int	check_rows_bottom(int *poss, int size, int *povs);

int	is_valid(int *poss, int size, int *grid, int num, int *povs)
{
	int	i;

	i = -1;
	while (++i < size)
		if (poss[grid[0] * size + i] == num || poss[i * size + grid[1]] == num)
			return (0);
	
	poss[grid[0] * size + grid[1]] = num;
	if (!check_rows_left(poss, size, povs)
		&& !check_rows_right(poss, size, povs)
		&& !check_rows_top(poss, size, povs)
		&& !check_rows_bottom(poss, size, povs))
	{
		poss[grid[0] * size + grid[1]] = 0;
		return (0);
	}
	
	poss[grid[0] * size + grid[1]] = 0;
	return (1);
}

void	handle_starting_poss(int *povs, int *poss, int size)
{
	int	i;
	int	counter;

	i = 0;
	while (++i <= size)
	{
		counter = i - 1;
		while (counter < size * size)
		{
			if (counter / size == 0 && povs[counter] == 1)
				poss[i - 1] = size;
			else if (counter / size == 1 && povs[counter] == 1)
				poss[(i - 1) * size + (size - 1)] = size;
			else if (counter / size == 2 && povs[counter] == 1)
				poss[size * size - i] = size;
			else if (counter / size == 3 && povs[counter] == 1)
				poss[(size - i) * size] = size;
			counter = counter + size;
		}
	}
}

int	solve(int *poss, int size, int *grid, int *povs)
{
	int	num;
	int	grid2[2];

	num = 0;
	if (grid[0] == size)
		return (1);
	if (grid[1] == size)
		return (solve(poss, size, add_to_row(grid, grid2), povs));
	if (poss[grid[0] * size + grid[1]] != 0)
		return (solve(poss, size, add_to_col(grid, grid2), povs));
	while (++num <= size)
	{
		if (is_valid(poss, size, grid, num, povs))
		{
			poss[grid[0] * size + grid[1]] = num;
			if (solve(poss, size, add_to_col(grid, grid2), povs))
				return (1);
			poss[grid[0] * size + grid[1]] = 0;
		}
	}
	return (0);
}

int	*solve_skyscrapper(int *povs, int size)
{
	int	*possibilities;
	int	grid[2];

	grid[0] = 0;
	grid[1] = 0;
	possibilities = (int *)malloc(size * size * 4);
	handle_starting_poss(povs, possibilities, size);
	if (solve(possibilities, size, grid, povs))
		return possibilities;
	free(possibilities);
	return NULL;
}

