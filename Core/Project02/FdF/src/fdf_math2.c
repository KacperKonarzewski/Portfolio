/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:53:05 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:33:24 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_cord(float matf[3], int cords[3])
{
	return (matf[0] * cords[0] + matf[1] * cords[1] + matf[2] * cords[2]);
}

double	get_percent(int current, int start, int end)
{
	double	distance;
	double	placement;

	distance = end - start;
	placement = current - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

int	get_color(int color1, int color2, double percent)
{
	int	r[3];
	int	g[3];
	int	b[3];

	r[0] = (color1 >> 16) & 0xFF;
	g[0] = (color1 >> 8) & 0xFF;
	b[0] = (color1) & 0xFF;
	r[1] = (color2 >> 16) & 0xFF;
	g[1] = (color2 >> 8) & 0xFF;
	b[1] = (color2) & 0xFF;
	r[2] = (int)(r[0] + (r[1] - r[0]) * percent);
	g[2] = (int)(g[0] + (g[1] - g[0]) * percent);
	b[2] = (int)(b[0] + (b[1] - b[0]) * percent);
	return ((r[2] << 16) | (g[2] << 8) | b[2]);
}
