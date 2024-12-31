/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:54:27 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 21:52:34 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_vertical(float m[3][3], t_data *img, t_vars *d)
{
	int		cords[3];
	int		i;
	int		j;
	t_point	point[2];

	i = -1;
	while (++i <= d->y)
	{
		j = -1;
		while (++j < d->x)
		{
			fill_cords(cords, d, i, j);
			point[0].x = get_cord(m[0], cords) + 1776 / 2 + d->offset_x;
			point[0].y = get_cord(m[1], cords) + 999 / 2 + d->offset_y;
			cords[0] = (j + 1) * 40 * d->sc - (d->x - 1) * (40 * d->sc) / 2;
			cords[2] = d->map[i][j + 1].z * d->tf * (2 + d->sc * 3);
			point[1].x = get_cord(m[0], cords) + 1776 / 2 + d->offset_x;
			point[1].y = get_cord(m[1], cords) + 999 / 2 + d->offset_y;
			mlx_put_line(img, point, d->map[i][j], d->map[i][j + 1]);
		}
	}
}

static void	draw_horizontal(float m[3][3], t_data *img, t_vars *d)
{
	int		cords[3];
	int		i;
	int		j;
	t_point	point[2];

	i = -1;
	while (++i < d->y)
	{
		j = -1;
		while (++j <= d->x)
		{
			fill_cords(cords, d, i, j);
			point[0].x = get_cord(m[0], cords) + 1776 / 2 + d->offset_x;
			point[0].y = get_cord(m[1], cords) + 999 / 2 + d->offset_y;
			cords[1] = (i + 1) * 40 * d->sc - (d->y - 1) * (40 * d->sc) / 2;
			cords[2] = d->map[i + 1][j].z * d->tf * (2 + d->sc * 3);
			point[1].x = get_cord(m[0], cords) + 1776 / 2 + d->offset_x;
			point[1].y = get_cord(m[1], cords) + 999 / 2 + d->offset_y;
			mlx_put_line(img, point, d->map[i][j], d->map[i + 1][j]);
		}
	}
}

void	draw_image(t_vars *data)
{
	float	m[3][3];
	float	scale_x;
	float	scale_y;
	float	scale;

	data->img.img = mlx_new_image(data->mlx, 1776, 999);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	get_final_matrix(data->cam, m);
	scale_x = 999.0f / (data->x * 40.0f + 40.0f);
	scale_y = 999.0f / (data->y * 40.0f + 40.0f);
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale > 1.3)
		scale = 1.3;
	else
		scale *= 0.75;
	data->sc = scale + data->zoom;
	draw_vertical(m, &data->img, data);
	draw_horizontal(m, &data->img, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	handle_input(int keysym, t_vars *data)
{
	if (check_rotation(keysym, data))
		return (0);
	if (check_zoom(keysym, data))
		return (0);
	if (check_misc(keysym, data))
		return (0);
	if (check_move(keysym, data))
		return (0);
	if (check_transformation(keysym, data))
		return (0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars		data;

	if (argc != 2)
		print_error("Bad amount of arguments! Exiting...");
	data.map = load_data(argv[1]);
	if (!data.map)
		print_error("Error with loading map! Exiting...");
	srand(time(NULL));
	init_camera(&data, 35, -35, 35);
	generate_palette(&data, 0xFFFFFF);
	init_mlx(&data);
	draw_image(&data);
	mlx_key_hook(data.win, &handle_input, &data);
	mlx_hook(data.win, 17, 0, &stop_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_image(data.mlx, data.img.img);
	mlx_destroy_display(data.mlx);
	clear_map(data.map);
	free(data.mlx);
}
