/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:56:32 by kkonarze          #+#    #+#             */
/*   Updated: 2025/03/14 08:56:28 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrixes.h"

//Function used for counting decimal places in a n number.
static int	count_number_len(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	print_matrix(int matrix[3][3])
{
	int	digit_lengths[3][3];
	int	col_width[3] = {0, 0, 0};
	int	border_width;
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			digit_lengths[i][j] = count_number_len(matrix[i][j]);
			if (digit_lengths[i][j] > col_width[j])
				col_width[j] = digit_lengths[i][j];
			j++;
		}
		i++;
	}
	border_width = col_width[0] + col_width[1] + col_width[2] + 2;
	printf("--%*s--\n", border_width - 2, "");
	i = 0;
	while (i < 3)
	{
		printf("|");
		j = 0;
		while (j < 3)
		{
			if (j > 0)
				printf(" ");
			printf("%*d", col_width[j], matrix[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
	printf("--%*s--\n", border_width - 2 , "");
}
