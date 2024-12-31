/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:07:43 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:27:18 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_color(int c[3], int r, int g, int b)
{
	c[0] = r;
	c[1] = g;
	c[2] = b;
}

static void	get_hue(int c[3], int hue)
{
	if (hue < 60)
		set_color(c, 255, (hue * 255) / 60, 0);
	else if (hue < 120)
		set_color(c, ((120 - hue) * 255) / 60, 255, 0);
	else if (hue < 180)
		set_color(c, 0, 255, ((hue - 120) * 255) / 60);
	else if (hue < 240)
		set_color(c, 0, ((240 - hue) * 255) / 60, 255);
	else if (hue < 300)
		set_color(c, ((hue - 240) * 255) / 60, 0, 255);
	else
		set_color(c, 255, 0, ((360 - hue) * 255) / 60);
}

void	generate_palette(t_vars *d, int base_color)
{
	int		i;
	int		j;
	int		current_color;
	int		color[3];
	int		hue;

	i = -1;
	while (++i <= d->y)
	{
		j = -1;
		while (++j <= d->x)
		{
			if (d->map[i][j].z == 0 && d->map[i][j].color == -1)
				d->map[i][j].color = base_color;
			else if (d->map[i][j].color == -1)
			{
				hue = (d->map[i][j].z * 5) % 360;
				get_hue(color, hue);
				current_color = (color[0] << 16) | (color[1] << 8) | color[2];
				d->map[i][j].color = current_color;
			}
		}
	}
}
