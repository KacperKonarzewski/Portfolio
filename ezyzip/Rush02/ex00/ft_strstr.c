/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejjime <alejjime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:58:53 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/08 22:46:05 by alejjime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	get_len(char *str, int i);
int	check_num(char *str);

int	ft_strstr(char *str, char *to_find)
{
	int	i;
	int	length;
	int	counter;

	counter = 0;
	i = 0;
	length = get_len(to_find, 0);
	while (str[i] != '\0' && to_find[counter] != '\0' && str[i] != ':')
	{
		if (str[i] == to_find[counter])
			counter++;
		else
			counter = 0;
		i++;
	}
	if (counter == length && str[i] == ':')
		return (1);
	return (0);
}

void	check_error(int *pop_error, int argc, char **argv)
{
	if (argc > 3 || argc < 2)
		*pop_error = 1;
	else if (argc == 2)
	{
		if (check_num(argv[1]))
			*pop_error = 1;
	}
	else
		if (check_num(argv[2]))
			*pop_error = 1;
}

void	fill_strfixed(char *strfixed, int length, char *str)
{
	int	i;

	i = -1;
	while (++i < 3)
		strfixed[i] = '0';
	i = -1;
	while (++i < (length + 2) / 3 * 3)
		strfixed[i + ((length * 2) % 3)] = str[i];
}
