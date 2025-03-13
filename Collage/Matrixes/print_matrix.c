/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:56:32 by kkonarze          #+#    #+#             */
/*   Updated: 2025/03/13 09:07:16 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	longest_line_width(int **digit_lenghts)
{
	int	i;
	int	j;
	int	tmp;
	int	tmp2;

	i = -1;
	tmp2 = 0;
	while (++i < 3)
	{
		tmp = 0;
		j = -1;
		while (++j < 3)
			tmp += digit_lenghts[i][j];
		if (tmp > tmp2)
			tmp2 = tmp;
	}
}

//Function used for counting decimal places in a n number.
static int	count_number_len(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	print_matrix(int **matrix)
{
	int	digit_lenghts[3][3];
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j)
			digit_lenghts[i][j] = count_number_len(matrix[i][j]);
	}
	i = -1;
	printf("--%*s--", digit_lenghts[0][j]);
}
