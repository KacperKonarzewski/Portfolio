/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:50:39 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:41:49 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_r_x(float alpha, float r_x[3][3])
{
	r_x[0][0] = 1;
	r_x[0][1] = 0;
	r_x[0][2] = 0;
	r_x[1][0] = 0;
	r_x[1][1] = cos(alpha);
	r_x[1][2] = -sin(alpha);
	r_x[2][0] = 0;
	r_x[2][1] = sin(alpha);
	r_x[2][2] = cos(alpha);
}

static void	create_r_y(float beta, float r_y[3][3])
{
	r_y[0][0] = cos(beta);
	r_y[0][1] = 0;
	r_y[0][2] = sin(beta);
	r_y[1][0] = 0;
	r_y[1][1] = 1;
	r_y[1][2] = 0;
	r_y[2][0] = -sin(beta);
	r_y[2][1] = 0;
	r_y[2][2] = cos(beta);
}

static void	create_r_z(float gamma, float r_z[3][3])
{
	r_z[0][0] = cos(gamma);
	r_z[0][1] = -sin(gamma);
	r_z[0][2] = 0;
	r_z[1][0] = sin(gamma);
	r_z[1][1] = cos(gamma);
	r_z[1][2] = 0;
	r_z[2][0] = 0;
	r_z[2][1] = 0;
	r_z[2][2] = 1;
}

void	multiply_matrix(float mat1[3][3], float mat2[3][3], float mat3[3][3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mat3[i][j] = 0;
			mat3[i][j] += mat1[i][0] * mat2[0][j];
			mat3[i][j] += mat1[i][1] * mat2[1][j];
			mat3[i][j] += mat1[i][2] * mat2[2][j];
			j++;
		}
		i++;
	}
}

void	get_final_matrix(t_camera cam, float matf[3][3])
{
	float	temp[3][3];
	float	r_x[3][3];
	float	r_y[3][3];
	float	r_z[3][3];

	create_r_x(cam.pitch, r_x);
	create_r_y(cam.yaw, r_y);
	create_r_z(cam.roll, r_z);
	multiply_matrix(r_z, r_y, temp);
	multiply_matrix(temp, r_x, matf);
}
