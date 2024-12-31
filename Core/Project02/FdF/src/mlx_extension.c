/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:06:22 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:38:26 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_mlx(t_vars *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		perror("Error");
		exit(-1);
	}
	mlx->win = mlx_new_window(mlx->mlx, 1776, 999, "Fdf");
	if (!mlx->win)
	{
		perror("Error");
		exit(-1);
	}
}

int	stop_loop(t_vars *d)
{
	mlx_loop_end(d->mlx);
	return (1);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1776 || y < 0 || y >= 999)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mlx_put_line(t_data *data, t_point cors[2], t_height z, t_height z2)
{
	t_bres	b;
	double	percent;

	init_bres(&b, cors);
	while (1)
	{
		percent = bres_percent(&b);
		my_mlx_pixel_put(data, b.cur.x, b.cur.y,
			get_color(z.color, z2.color, percent));
		if (b.cur.x == b.x1 && b.cur.y == b.y1)
			break ;
		bres_step(&b);
	}
}
