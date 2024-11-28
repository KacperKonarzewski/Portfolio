/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:50:23 by dszafran          #+#    #+#             */
/*   Updated: 2024/09/11 22:33:16 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>

void	open_file(char *filename, int *fd);
void	create_fds(int *fds, char *filename, int flag);
void	close_fds(int *fds);
void	free_map(char **map, int len);
char	*get_info_line(char *filename);
char	*get_info(char *filename);
int		line_count(char *filename);
int		line_size(int fd);
int		get_len(char *arr);

int	check_arr(int fd, char *arr, int len)
{
	int		i;
	char	c;

	i = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c != '\n' && c != arr[0] && c != arr[1])
			return (0);
		if (c == '\n')
			i++;
	}
	if (len != i)
		return (0);
	return (1);
}

int	check_map(char *filename)
{
	int		fd;
	char	*arr;
	int		i;
	int		len;

	arr = get_info(filename);
	len = line_count(filename);
	open_file(filename, &fd);
	if (!arr || len <= 0 || fd == -1)
	{
		free(arr);
		return (0);
	}
	line_size(fd);
	i = check_arr(fd, arr, len);
	close(fd);
	free(arr);
	if (i == 0)
		return (0);
	return (1);
}

int	check_line_lens(char **map, int len)
{
	int	i;

	i = 1;
	while (i < len)
	{
		if (get_len(map[i]) != get_len(map[i - 1]))
			return (0);
		i++;
	}
	return (1);
}

void	write_line(int fd, char *map)
{
	int		i;
	char	c;

	i = 0;
	while (read(fd, &c, 1) > 0 && c != '\n')
	{
		map[i] = c;
		i++;
	}
	map[i] = '\0';
}

char	**read_map(char *filename)
{
	int		fds[2];
	int		i;
	int		len;
	int		length;
	char	**map;

	if (check_map(filename) == 0)
		return (NULL);
	len = line_count(filename);
	create_fds(fds, filename, 1);
	map = (char **)malloc(len * sizeof(char *));
	i = -1;
	while (++i < len)
	{
		length = line_size(fds[0]);
		map[i] = (char *)malloc(length + 1);
		write_line(fds[1], map[i]);
	}
	close_fds(fds);
	if (check_line_lens(map, len) == 0)
	{
		free_map(map, len);
		return (NULL);
	}
	return (map);
}
