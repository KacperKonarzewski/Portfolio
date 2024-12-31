/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:49:41 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:41:54 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef M_PI

#  define M_PI 3.14159265358979323846264338327950288

# endif

# include <math.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h" 
# include <X11/keysym.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_height
{
	int	z;
	int	color;
	int	last;
}				t_height;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_camera
{
	float	pitch;
	float	yaw;
	float	roll;
}				t_camera;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_camera	cam;
	t_height	**map;
	float		sc;
	float		zoom;
	int			offset_x;
	int			offset_y;
	double		tf;
	int			x;
	int			y;
}				t_vars;

typedef struct s_bres
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	t_point		dcors;
	t_point		cur;
}	t_bres;

//hooks
int			check_misc(int keysym, t_vars *data);
int			check_rotation(int keysym, t_vars *data);
int			check_zoom(int keysym, t_vars *data);
int			check_move(int keysym, t_vars *data);
int			check_transformation(int keysym, t_vars *data);
//main
void		draw_image(t_vars *data);
//mlx_extension
void		mlx_put_line(t_data *data, t_point cors[2], t_height z,
				t_height z2);
void		init_mlx(t_vars *mlx);
int			stop_loop(t_vars *d);
//fdf_utils
int			count_lines(char *path);
void		clear_split(char **strs);
void		print_error(char *error);
void		init_camera(t_vars *data, float p, float y, float r);
void		clear_map(t_height **map);
//fdf_map
int			get_map_x(t_height *map);
int			get_map_y(t_height **map);
t_height	**load_data(char *path);
//fdf_math
float		get_cord(float matf[3], int cords[3]);
void		get_final_matrix(t_camera cam, float matf[3][3]);
void		multiply_matrix(float mat1[3][3], float mat2[3][3],
				float mat3[3][3]);
void		fill_cords(int cords[3], t_vars *d, int i, int j);
int			get_color(int color1, int color2, double percent);
double		get_percent(int current, int start, int end);
//color_palette
void		generate_palette(t_vars *d, int base_color);
//fdf_generate_map
void		gen_map(void);
//bresenham
void		init_bres(t_bres *b, t_point cors[2]);
double		bres_percent(t_bres *b);
void		bres_step(t_bres *b);

#endif