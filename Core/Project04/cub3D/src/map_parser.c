/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacper <kacper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:24:20 by kkonarze          #+#    #+#             */
/*   Updated: 2025/03/02 19:42:30 by kacper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	find_texture(char *side, t_textures *current)
{
	if (ft_strncmp(side, "NO", 3) == 0)
		*current = NO;
	else if (ft_strncmp(side, "SO", 3) == 0)
		*current = SO;
	else if (ft_strncmp(side, "WE", 3) == 0)
		*current = WE;
	else if (ft_strncmp(side, "EA", 3) == 0)
		*current = EA;
	else if (ft_strncmp(side, "F", 2) == 0)
		*current = F;
	else if (ft_strncmp(side, "C", 2) == 0)
		*current = C;
	else
		*current = -1;
}

static void	init_empty_textures(t_map *map)
{
	map->textures[0].side = NO;
	map->textures[1].side = SO;
	map->textures[2].side = WE;
	map->textures[3].side = EA;
	map->textures[4].side = F;
	map->textures[5].side = C;
	map->textures[0].path = NULL;
	map->textures[1].path = NULL;
	map->textures[2].path = NULL;
	map->textures[3].path = NULL;
	map->textures[4].path = NULL;
	map->textures[5].path = NULL;
}

static bool	check_order(char *line, t_map *map)
{
	static t_textures	last = NO;
	static bool			used_textures[6] = {false};
	char				**splited;
	t_textures			current;

	splited = ft_split(line, " ");
	find_texture(splited[0], &current);
	if ((int)current == -1)
		return (ft_free_split(splited), true);
	if (used_textures[current])
		return (ft_free_split(splited), error(false, \
		"Duplicate texture detected!"), true);
	if (current < last)
		return (ft_free_split(splited), error(false, \
		"Wrong map textures order!"), true);
	if (!splited[1])
		return (ft_free_split(splited), error(false, \
		"Missing texture path!"), true);
	last = current;
	used_textures[current] = true;
	map->textures[current].path = ft_strdup(splited[1]);
	return (ft_free_split(splited), false);
}

static bool	check_if_empty(char **line, int fd)
{
	int	i;

	i = 0;
	while ((*line)[i] && (*line)[i] == ' ')
		i++;
	if ((*line)[i] != 0 && (*line)[i] != '\n')
		return (false);
	free(*line);
	*line = get_next_line(fd);
	return (true);
}

t_map	create_map(int fd)
{
	char	buffer[100][100];
	char	*line;
	t_map	map;

	init_empty_textures(&map);
	line = get_next_line(fd);
	while (line)
	{
		if (check_if_empty(&line, fd))
			continue ;
		if (check_order(line, &map))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (check_textures(map))
		return (free(line), free_texures(&map), error(false, \
				"Missing texture side!"), map);
	load_map(&line, fd, buffer);
	if (validate_chars(buffer) && validate_frame(buffer, count_rows(buffer)))
		return (free_textures(&map), error(false, "Wrong map!"), map);
	if (convert_buffer(&map, buffer, count_rows(buffer)))
		return (free_textures(&map), error(false, "Error converting"), map);
	return (map);
}
