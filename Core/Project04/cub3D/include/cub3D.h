/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:38:47 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/19 10:57:16 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef M_PI

#  define M_PI 3.14159265358979323846264338327950288

# endif

# define W_HEIGHT 900
# define W_WIDTH 1600

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h" 
# include <X11/keysym.h>

typedef enum e_textures
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}				t_textures;

typedef enum e_object
{
	EMPTY,
	WALL,
	DOOR
}				t_object;

typedef struct s_texture_info
{
	t_textures	side;
	int			color;
	char		*path;
}				t_texture_info;

typedef struct t_tile
{
	t_object	type;
	int			last;
	bool		opened;
}				t_point;

typedef struct s_map
{
	t_point			**points;
	t_texture_info	textures[6];
	int				map_height;
	int				map_width;
}				t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_camera
{
	float	pitch;
	float	yaw;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}				t_camera;

typedef struct s_player
{
	t_camera	cam;
	float		x_pos;
	float		y_pos;
	float		move_speed;
}				t_player;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_data			img;
	t_player		player;
	t_map			map;
}				t_vars;

// utils.c

void	error(bool type, char *message);

// init.c

void	init_vars(t_vars **vars, char *map);

// map_parser.c

t_map	create_map(int fd);

// map_parser2.c

bool	check_textures(t_map map);
void	free_texures(t_map *map);

#endif