/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:46:27 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 17:42:27 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_error(char *error)
{
	ft_printf(error);
	exit(-1);
}

void	clear_map(t_height **map)
{
	int	i;

	i = 0;
	while (map[i][get_map_x(map[i])].last != 0)
		free(map[i++]);
	free(map[i]);
	free(map);
}

void	clear_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
		free(strs[i++]);
	free(strs[i]);
	free(strs);
}

int	count_lines(char *path)
{
	char	*line;
	int		fd;
	int		lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		exit(-1);
	}
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		lines++;
	}
	close(fd);
	return (lines);
}

void	init_camera(t_vars *data, float p, float y, float r)
{
	data->cam.pitch = p * M_PI / 180.0;
	data->cam.yaw = y * M_PI / 180.0;
	data->cam.roll = r * M_PI / 180.0;
	data->zoom = 0.0f;
	data->offset_x = 0;
	data->offset_y = 0;
	data->tf = 1;
	data->x = get_map_x(data->map[0]);
	data->y = get_map_y(data->map);
}
