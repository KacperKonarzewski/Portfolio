/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:54:44 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/11 21:55:09 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	**read_input(int i, char *info, char *buffer, int line_end);
char	*read_info(int i, char *buffer);
int		line_count_input(char *info);
int		ft_len(char *str, int i);
void	ft_error(char *str, int stop);

void	fill_buffer(char *buffer, char c, int *line_end, int *i)
{
	if (c != '\n')
	{
		buffer[++(*i)] = c;
	}
	else
	{
		buffer[*i + 1] = '\0';
		*line_end = 1;
	}
}

int	fill_line(char *buffer, char *map, int *j, char *info)
{
	int	str_i;

	if (*j + 1 == line_count_input(info))
		return (NULL);
	map[++(*j)] = (char *)malloc(i + 2);
	if (!map[j])
		return (NULL);
	str_i = -1;
	while (buffer[++str_i])
		map[str_i] = buffer[str_i];
	map[str_i] = '\0';
}

void	clear_mallocs(char *info, char *infochars, char *buffer)
{
	free(info);
	free(infochars);
	free(buffer);
}

int	*get_inputs(char *info, char *infochars, char **map)
{
	char	*buffer;
	
	buffer = (char *)malloc(1000000);
	if (!buffer)
		ft_error("map error", 1);
	
	if (!map || !infochars || !check_map_input(map, info))
	{
		clear_mallocs(info, infochars, buffer);
		ft_error("map error", 1);
	}
	map = read_input(-1, info, buffer, 0);
	if (!map)
	{
		clear_mallocs(info, infochars, buffer);
		ft_error("map error", 1);
	}
	write_square(map, infochars, line_count_input(info));
	free(info);
	free(buffer);
}
