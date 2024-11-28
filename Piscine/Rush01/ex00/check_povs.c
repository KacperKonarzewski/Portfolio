/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_povs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:54:42 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/01 22:55:02 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	count_visible_skyscrapers(int *arr, int size) 
{
	int 	count;
	int 	max_height;
	int	i;
	
	count = 0;
	max_height = 0;
	i = -1;
	while (++i < size) {
		if (arr[i] > max_height) 
		{
    			max_height = arr[i];
    			count++;
		}
	}
	return (count);
}

int check_rows_left(int *poss, int size, int *povs)
{
	int	row;
	int	view_count;

	row = -1;
	while(++row < size)
	{
		view_count = count_visible_skyscrapers(&poss[row * size], size);
		if (povs[row] != 0 && view_count != povs[row])
			return 0;
	}
	return (1);
}

int check_rows_right(int *poss, int size, int *povs)
{
	int	row;
	int	col;
	int	view_count;
	int	reverse_row[size];

	row = -1;
	col = -1;
	while (++row < size)
	{
		while (++col < size)
    			reverse_row[col] = poss[row * size + size - 1 - col];
		view_count = count_visible_skyscrapers(reverse_row, size);
		if (povs[size + row] != 0 && view_count != povs[size + row])
    			return 0;
    	}
    	return (1);
}

int check_rows_top(int *poss, int size, int *povs)
{
	int	row;
	int	col;
	int	view_count;
	int	col_arr[size];

	row = -1;
	col = -1;
	while (++col < size)
	{
		while (++row < size)
	    		col_arr[row] = poss[row * size + col];
		view_count = count_visible_skyscrapers(col_arr, size);
		if (povs[2 * size + col] != 0 && view_count != povs[2 * size + col])
			return 0;
	}
	return (1);
}

int check_rows_bottom(int *poss, int size, int *povs)
{
	int	row;
	int	col;
	int	view_count;
	int	reverse_col[size];

	row = -1;
	col = -1;
	while (++col < size) {
		while (++row < size)
			reverse_col[row] = poss[(size - 1 - row) * size + col];
		view_count = count_visible_skyscrapers(reverse_col, size);
		if (povs[3 * size + col] != 0 && view_count != povs[3 * size + col])
			return (0);
	}
	return (1);
}
