/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:24:20 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/24 10:18:30 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	validate_chars(char buffer[100][100])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 100 && buffer[i])
	{
		j = -1;
		while (++j < 100 && buffer[i][j])
			if (!ft_strchr(" 012NSEW", buffer[i][j]))
				return (true);
	}
	return (false);
}

static void	init_buffer(char buffer[100][100])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 100)
	{
		j = -1;
		while (++j < 100)
			buffer[i][j] = 0;
	}
}

void	load_map(char **line, int fd, char buffer[100][100])
{
	int		i;
	int		j;

	init_buffer(buffer);
	j = -1;
	while (*line && ++j > -1)
	{
		i = -1;
		while (j < 100 && ++i < 100 && (*line)[i] && (*line) != '\n')
			buffer[j][i] = (*line)[i];
		free(*line);
		*line = get_next_line(fd);
	}
	return (buffer);
}

void	free_texures(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 6)
		if (map->textures[i].path)
			free(map->textures[i].path);
}

bool	check_textures(t_map map)
{
	int	i;

	i = -1;
	while (++i < 6)
		if (map.textures[i].path == NULL)
			return (true);
	return (false);
}
