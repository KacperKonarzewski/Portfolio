/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:23:56 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/09 23:36:12 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_len(char *str, int i);

int	get_maximum_square(int lines, int linelen)
{
	if (lines > linelen)
		return (linelen);
	return (lines);
}

int	check_square(int square, int *coords, char **map, char *info)
{
	int	row;
	int	col;

	row = -1;
	while (++row < square)
	{
		col = -1;
		while (++col < square)
			if (map[coords[0] + row][coords[1] + col] == info[1])
				return (0);
	}
	return (1);
}

void	write_map(int *coords, int square, char **map, char *info)
{
	int	row;
	int	col;

	row = -1;
	while (++row < square)
	{
		col = -1;
		while (++col < square)
			map[coords[0] + row][coords[1] + col] = info[2];
	}
}

void	find_square(int lines, int square, char **map, char *info)
{
	int	max_row;
	int	max_column;
	int	coords[2];
	int	check;

	if (square < 0)
		return ;
	coords[0] = -1;
	max_column = ft_len(map[0], 0) - square;
	max_row = lines - square;
	check = 0;
	while (check == 0 && ++coords[0] <= max_row)
	{
		coords[1] = -1;
		while (check == 0 && ++coords[1] <= max_column)
			if (check_square(square, coords, map, info))
				check = 1;
	}
	if (check)
		write_map(coords, square, map, info);
	else
		find_square(lines, square - 1, map, info);
	return ;
}
