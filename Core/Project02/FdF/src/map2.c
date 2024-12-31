/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:03:31 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 17:43:27 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map_y(t_height **map)
{
	int	i;
	int	last;

	i = 0;
	last = get_map_x(map[0]);
	while (map[i][last].last != 0)
		i++;
	return (i);
}

void	fill_cords(int cords[3], t_vars *d, int i, int j)
{
	cords[0] = j * 40 * d->sc - (d->x - 1) * (40 * d->sc) / 2;
	cords[1] = i * 40 * d->sc - (d->y - 1) * (40 * d->sc) / 2;
	cords[2] = d->map[i][j].z * d->tf * (2 + d->sc * 3);
}
