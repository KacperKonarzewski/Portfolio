/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejjime <alejjime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:10:40 by alejjime          #+#    #+#             */
/*   Updated: 2024/09/08 22:48:32 by alejjime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	print_thousand(int len, int argc, char **argv);
void	write_l(char *num, int argc, char **argv, int len);
void	write_d(char *num, int argc, char **argv, int len);
void	write_h(char *num, int argc, char **argv, int len);
void	write_t(char *num, int argc, char **argv, int len);
int		line_write(char *line);
int		ft_strstr(char *str, char *to_find);
int		get_len(char *str, int i);
void	open_dict(int *fds, int argc, char **argv);
void	close_dict(int *fds);
void	print_thousand(int len, int argc, char **argv);

int	line_length(int fd_read, int i, int ctr, char c)
{
	while (read(fd_read, &c, 1) > 0 && c != '\n')
	{
		if (ctr == 0 && c != 20 && c != 9 && (c < 11 || c > 13))
		{
			if (c == ':')
				ctr++;
			i++;
		}
		else if (ctr == 1 && c != 20 && c != 9 && (c < 11 || c > 13))
		{
			ctr++;
			i++;
		}
		else if (c > 31 && c < 127)
			i++;
	}
	return (i);
}

int	check_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] < 32 || line[i] > 126)
			return (1);
	return (0);
}

void	set_line(char *line, int fd_write, int i, int ctr)
{
	char	c;

	while (read(fd_write, &c, 1) > 0 && c != '\n')
	{
		if (ctr == 0 && c != 20 && c != 9 && (c < 11 || c > 13))
		{
			if (c == ':')
				ctr++;
			line[i] = c;
			i++;
		}
		else if (ctr == 1 && c != 20 && c != 9 && (c < 11 || c > 13))
		{
			ctr++;
			line[i] = c;
			i++;
		}
		else
		{
			line[i] = c;
			i++;
		}
	}
	line[i] = '\0';
}

void	search_lines(char *num, int argc, char **argv, int placement)
{
	int		length;
	char	*line;
	char	c;
	int		fds[2];
	int		found;

	c = '\0';
	found = 0;
	open_dict(fds, argc, argv);
	if (fds[0] == -1 || fds[1] == -1)
		write(1, "Missing file\n", 14);
	if (get_len(argv[1], 0) != placement || get_len(num, 0) > 2)
		write(1, " ", 1);
	while (1)
	{
		length = line_length(fds[0], 0, 0, c);
		line = malloc(length + 1);
		set_line(line, fds[1], 0, 0);
		if (ft_strstr(line, num))
			found = line_write(line);
		free(line);
		if (read(fds[0], &c, 1) == 0 || found)
			break ;
	}
	close_dict(fds);
}

void	num_to_str(char *num, int len, int argc, char **argv)
{
	int	temp;

	temp = len;
	len++;
	if (num[0] > '0')
		write_h(num, argc, argv, len);
	len--;
	if (num[1] == '1')
		write_t(num, argc, argv, len);
	else
	{
		if (num[1] != '0')
			write_d(num, argc, argv, len);
		len--;
		if (num[2] != '0')
			write_l(num, argc, argv, len);
	}
	if ((num[0] != '0' || num[1] != '0' || num[2] != '0') && temp >= 3)
		print_thousand(temp - 1, argc, argv);
}
