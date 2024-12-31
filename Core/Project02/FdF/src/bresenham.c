/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:36:11 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:38:45 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_bres(t_bres *b, t_point cors[2])
{
	b->x0 = cors[0].x;
	b->y0 = cors[0].y;
	b->x1 = cors[1].x;
	b->y1 = cors[1].y;
	b->dcors.x = abs(b->x1 - b->x0);
	b->dcors.y = abs(b->y1 - b->y0);
	if (b->x0 < b->x1)
		b->sx = 1;
	else
		b->sx = -1;
	if (b->y0 < b->y1)
		b->sy = 1;
	else
		b->sy = -1;
	b->err = b->dcors.x - b->dcors.y;
	b->cur.x = b->x0;
	b->cur.y = b->y0;
}

double	bres_percent(t_bres *b)
{
	if (b->dcors.x > b->dcors.y)
		return (get_percent(b->cur.x, b->x0, b->x1));
	return (get_percent(b->cur.y, b->y0, b->y1));
}

void	bres_step(t_bres *b)
{
	b->e2 = b->err * 2;
	if (b->e2 > -(b->dcors.y))
	{
		b->err -= b->dcors.y;
		b->cur.x += b->sx;
	}
	if (b->e2 < b->dcors.x)
	{
		b->err += b->dcors.x;
		b->cur.y += b->sy;
	}
}
