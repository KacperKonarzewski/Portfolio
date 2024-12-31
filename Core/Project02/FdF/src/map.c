/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:18:21 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/30 20:49:55 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map_x(t_height *map)
{
	int	i;

	i = 0;
	while (map[i].last != 0 && map[i].last != 2)
		i++;
	return (i);
}

static int	base_to_dec(char *nbr, char *base)
{
	int		value;
	int		i;

	value = 0;
	nbr += 3;
	while (*nbr)
	{
		i = 0;
		while (i < 16)
		{
			if (ft_tolower(*nbr) == base[i])
			{
				value = value * 16 + i;
				break ;
			}
			i++;
		}
		nbr++;
	}
	return (value);
}

static t_height	*cast_line(char *line)
{
	char		**sep_line;
	t_height	*h_line;
	int			i;

	i = 0;
	sep_line = ft_split(line, " \n");
	while (sep_line[i] != 0)
		i++;
	h_line = malloc(sizeof(t_height) * i);
	if (!h_line)
		return (NULL);
	i = -1;
	while (sep_line[++i] != 0)
	{
		h_line[i].z = ft_atoi(sep_line[i]);
		if (ft_strnstr(sep_line[i], ",0x", ft_strlen(sep_line[i])))
			h_line[i].color = base_to_dec(sep_line[i], "0123456789abcdef");
		else
			h_line[i].color = -1;
		h_line[i].last = 1;
	}
	h_line[i - 1].last = 2;
	clear_split(sep_line);
	return (h_line);
}

static t_height	**create_map(int fd, int lines)
{
	t_height	**map;
	char		*line;
	int			i;
	int			j;

	if (lines == 0)
		return (NULL);
	map = (t_height **)malloc(lines * sizeof(t_height *));
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i++] = cast_line(line);
		free(line);
		line = get_next_line(fd);
	}
	j = 0;
	while (map[i - 1][j].last != 2)
		j++;
	map[i - 1][j].last = 0;
	return (map);
}

t_height	**load_data(char *path)
{
	int			fd;
	t_height	**map;

	if (!ft_strnstr(path, ".fdf", ft_strlen(path)))
		print_error("File is not in the extension .fdf! Exiting...");
	fd = open(path, O_RDONLY);
	map = create_map(fd, count_lines(path));
	close(fd);
	return (map);
}
