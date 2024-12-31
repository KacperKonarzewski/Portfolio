/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 02:47:24 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:01:28 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_misc(int keysym, t_vars *data)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(data->mlx);
		return (1);
	}
	else if (keysym == XK_r)
		init_camera(data, 35, -35, 35);
	else if (keysym == XK_g)
	{
		gen_map();
		if (data->map)
		{
			clear_map(data->map);
			data->map = NULL;
		}
		data->map = load_data("maps/random.fdf");
		init_camera(data, 35, -35, 35);
		generate_palette(data, 0xFFFFFF);
	}
	else
		return (0);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img);
	draw_image(data);
	return (1);
}

int	check_rotation(int keysym, t_vars *data)
{
	if (keysym == XK_a)
		data->cam.roll += (-5 * M_PI / 180.0);
	else if (keysym == XK_d)
		data->cam.roll += (5 * M_PI / 180.0);
	else if (keysym == XK_w)
		data->cam.pitch += (5 * M_PI / 180.0);
	else if (keysym == XK_s)
		data->cam.pitch += (-5 * M_PI / 180.0);
	else if (keysym == XK_q)
		data->cam.yaw += (5 * M_PI / 180.0);
	else if (keysym == XK_e)
		data->cam.yaw += (-5 * M_PI / 180.0);
	else
		return (0);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img);
	draw_image(data);
	return (1);
}

int	check_zoom(int keysym, t_vars *data)
{
	if (keysym == XK_z)
		data->zoom += data->sc * 0.05;
	else if (keysym == XK_x)
		data->zoom -= data->sc * 0.05;
	else
		return (0);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img);
	draw_image(data);
	return (1);
}

int	check_move(int keysym, t_vars *data)
{
	if (keysym == XK_Left)
		data->offset_x -= 10;
	else if (keysym == XK_Right)
		data->offset_x += 10;
	else if (keysym == XK_Up)
		data->offset_y -= 10;
	else if (keysym == XK_Down)
		data->offset_y += 10;
	else
		return (0);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img);
	draw_image(data);
	return (1);
}

int	check_transformation(int keysym, t_vars *data)
{
	if (keysym == XK_minus)
	{
		if (data->tf >= 0.2)
			data->tf -= 0.1;
		else
			return (1);
	}
	else if (keysym == XK_equal)
		data->tf += 0.1;
	else
		return (0);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img);
	draw_image(data);
	return (1);
}
