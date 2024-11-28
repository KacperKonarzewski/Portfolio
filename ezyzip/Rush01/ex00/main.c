/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:34:49 by dszafran          #+#    #+#             */
/*   Updated: 2024/09/01 22:05:40 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	get_len(char *str);
int	get_size(int len);
int	check_str(int size, char *str);
int	*num_arr(int size, char *str);

void	write_error(void)
{
	write(1, "Error\n", 6);
}

int	*preprocess(int *size, char *str)
{
	int	len;
	int	*arr;
	int	i;

	len = get_len(str);
	if (len == 0)
		write_error();
	*size = get_size(len);
	if (*size == 0)
		write_error();
	if (check_str(*size, str) == 0)
		write_error();
	arr = num_arr(*size, str);
	if (arr)
		return (&arr[0]);
	write_error();
}

int	main(int argc, char **argv)
{
	int	size;
	int	*ptr;
	int	*solvedarray;

	size = 0;
	if (argc != 2)
	{
		write_error();
	}
	else
	{
		ptr = preprocess(&size, &argv[1][0]);
	}
	return (0);
}
