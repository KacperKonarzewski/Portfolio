/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:12:46 by dszafran          #+#    #+#             */
/*   Updated: 2024/09/01 21:41:48 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	get_size(int len)
{
	int	sizes[9];
	int	i;

	if ((len + 1) % 2 != 0)
		return (0);
	i = 1;
	while (i < 10)
	{
		sizes[i - 1] = i;
		i++;
	}
	i = 0;
	while (sizes[i])
	{
		if ((len + 1) / 2 == sizes[i] * sizes[i])
		{
			return (sizes[i]);
		}
		i++;
	}
	return (0);
}

int	check_str(int size, char *str)
{
	char	max;
	int		i;

	max = '0' + size;
	i = 0;
	while (str[i])
	{
		if ((str[i] < '1' || str[i] > max) && str[i] != ' ')
			return (0);
		i++;
	}
	i = 1;
	while (str[i])
	{
		if (str[i] != ' ' && (str[i - 1] < '1' || str[i - 1] > max))
			return (0);
		i += 2;
	}
	if (str[i - 1] < '1' || str[i - 1] > max)
		return (0);
	return (size);
}

int	*num_arr(int size, char *str)
{
	int	*ptr;
	int	i;
	int	j;

	ptr = (int *)malloc(size * 4 * 4);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			ptr[j] = str[i] - 48;
			j++;
		}
		i++;
	}
	return (ptr);
}
