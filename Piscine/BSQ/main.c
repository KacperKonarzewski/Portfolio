/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:33:41 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/11 22:00:56 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int		get_inputs(char *info, char *infochars, char **map);
void	fill_buffer(char *buffer, char c, int *line_end, int *i);
void	fill_line(char *buffer, char *map, int *j, char *info);
void	find_square(int lines, int square, char **map, char *info);
void	ft_error(char *str, int stop);
char	*get_info(char *filename);
char	**read_map(char *argv);
char	*get_info_input(char *info);
int		check_map_input(char **map, char *info);
int		line_count(char *filename);
int		ft_len(char *str, int i);
int		get_maximum_square(int lines, int linelen);
int		line_count_input(char *info);

void	free_map(char **map, int lines)
{
	int	row;

	row = -1;
	while (++row < lines)
		free(map[row]);
	free(map);
}

void	write_square(char **map, char *info, int lines)
{
	int		square;
	int		row;
	int		col;

	square = get_maximum_square(lines, ft_len(map[0], 0));
	find_square(lines, square, map, info);
	row = -1;
	while (++row < lines)
	{
		col = -1;
		while (++col < ft_len(map[0], 0))
			write(1, &map[row][col], 1);
		write(1, "\n", 1);
	}
	free(info);
	free_map(map, lines);
}

char	*read_info(int i)
{
	char	*buffer;
	char	*info;
	char	first;

	buffer = (char *)malloc(1000000);
	while (read(0, &first, 1) > 0 && first != '\n')
		buffer[++i] = first;
	buffer[i + 1] = '\0';
	info = (char *)malloc(i + 2);
	if (!info)
		return (NULL);
	i = -1;
	while (buffer[++i])
		info[i] = buffer[i];
	info[i] = '\0';
	free(buffer);
	return (info);
}

void	read_input(int i, char *info, char *buffer, char **map)
{
	int	line_end;
	char	c;
	int		j;

	j = -1;
	line_end = 0;
	while (read(0, &c, 1) > 0)
	{
		fill_buffer(buffer, c, &line_end, &i);
		if (line_end)
		{
			fill_line(buffer, map[j], &j, info);
			line_end = 0;
			i = -1;
		}
	}
}

int	main(int argc, char **argv)
{
	int		i;
	char	**map;
	char	*info;
	char	*infochars;

	i = 0;
	if (argc < 2)
	{
		info = read_info(-1);
		infochars = get_info_input(info);
		map = (char **)malloc(line_count_input(info) * sizeof(char *) + 1);
		if(!(get_inputs(info, infochars, map)))
			return (1);
	}
	while (++i < argc)
	{
		map = read_map(argv[i]);
		if (map == NULL)
		{
			ft_error("map error", 0);
			continue ;
		}
		write_square(map, get_info(argv[i]), line_count(argv[i]));
		write(1, "\n", 1);
	}
}
