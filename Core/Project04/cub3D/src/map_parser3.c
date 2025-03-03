/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacper <kacper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:49:09 by kkonarze          #+#    #+#             */
/*   Updated: 2025/03/02 19:45:35 by kacper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	count_rows(char **buffer)
{
	int	i;

	i = -1;
	while (buffer[++i][0])
		;
	return (i);
}

static int	count_width(char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
		;
	return (i);
}

bool	validate_frame(char buffer[100][100], int rows)
{
	int		i;
	int		j;
	int		*map_rows;
	bool	leaking;

	map_rows = malloc(rows * sizeof(int));
	if (!map_rows)
		return (true);
	i = -1;
	while (++i < rows)
		map_rows[i] = (int)ft_strlen(buffer[i]);
	i = -1;
	while (!leaking && ++i < rows)
	{
		j = -1;
		while (!leaking && ++j < map_rows[i])
			if (buffer[i][j] == '0' || buffer[i][j] == '2')
				if ((i == 0 || j >= map_rows[i - 1] || buffer[i - 1][j] == \
' ') || (i == rows - 1 || j >= map_rows[i + 1] || buffer[i + 1][j] == ' ') \
	|| (j == 0 || buffer[i][j - 1] == ' ') || (j == map_rows[i] - 1 || \
		buffer[i][j + 1] == ' '))
					leaking = true;
	}
	return (leaking);
}

bool	convert_buffer(t_map *map, char buffer[100][100], int rows)
{
	int	i;
	int	j;
	int	row_width;

	i = -1;
	map->points = (t_point **)malloc(rows * sizeof(t_point *));
	if (!map->points)
		return (true);
	while (++i < rows)
	{
		row_width = count_width(buffer[i]);
	}
	
}
