/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejjime <alejjime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:33:05 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/08 22:46:04 by alejjime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	fill_strfixed(char *strfixed, int length, char *str);
int		check_file(int argc, char **argv);
void	num_to_str(char *num, int len, int argc, char **argv);
void	search_lines(char *num, int argc, char **argv, int placement);
void	open_dict(int *fd_read, int *fd_write, int argc, char **argv);
void	close_dict(int *fd_read, int *fd_write);
void	check_error(int *pop_error, int argc, char **argv);

int	check_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] > '9' || str[i] < '0')
			return (1);
	return (0);
}

int	get_len(char *str, int i)
{
	while (str[i])
		i++;
	return (i);
}

void	word_proccesor(char *str, int argc, char **argv)
{
	int		length;
	char	*strfixed;
	int		i;
	char	set[3];

	length = get_len(str, 0);
	if (length == 1 && str[0] == '0')
	{
		search_lines("0", argc, argv, length);
		return ;
	}
	strfixed = malloc(((length + 2) / 3) * 3);
	fill_strfixed(strfixed, length, str);
	i = 0;
	while (i <= get_len(strfixed, 0) - 1)
	{
		set[0] = strfixed[i];
		set[1] = strfixed[i + 1];
		set[2] = strfixed[i + 2];
		num_to_str(set, get_len(strfixed, 0) - 1 - i, argc, argv);
		i = i + 3;
	}
	free(strfixed);
}

int	main(int argc, char **argv)
{
	int	pop_error;

	pop_error = 0;
	check_error(&pop_error, argc, argv);
	if (pop_error)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (check_file(argc, argv))
		return (1);
	if (argc == 2)
		word_proccesor(argv[1], argc, argv);
	else
		word_proccesor(argv[2], argc, argv);
	write(1, "\n", 1);
	return (0);
}

int	check_file(int argc, char **argv)
{
	int		fd_read;
	int		fd_write;
	int		check;

	check = 1;
	open_dict(&fd_read, &fd_write, argc, argv);
	if (fd_read == -1 || fd_write == -1)
		write(1, "Missing file\n", 14);
	else
		check = 0;
	close_dict(&fd_read, &fd_write);
	return (check);
}
