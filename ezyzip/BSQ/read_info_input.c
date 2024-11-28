/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_info_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:45:46 by dszafran          #+#    #+#             */
/*   Updated: 2024/09/11 22:39:55 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	get_len(char *arr);

int	line_count_input(char *info)
{
	int	i;
	int	sum;
	int	len;

	len = get_len(info);
	if (len < 1)
		return (0);
	i = -1;
	sum = 0;
	while (++i < len - 3)
	{
		if (info[i] < '0' || info[i] > '9')
			return (0);
		sum = sum * 10 + (info[i] - 48);
	}
	if (sum <= 0)
		return (0);
	return (sum);
}

char	*get_info_input(char *info)
{
	char	*arr;
	int		i;
	int		len;

	len = get_len(info);
	if (len < 1)
		return (NULL);
	arr = (char *)malloc(4);
	if (!arr)
	{
		free(arr);
		return (NULL);
	}
	i = -1;
	while (++i < 3)
		arr[i] = info[len - 3 + i];
	arr[3] = '\0';
	if (arr[0] == arr[1] || arr[0] == arr[2] || arr[1] == arr[2])
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

int	check_chars(char **map, char *arr, int len)
{
	int	i;
	int	j;
	int	l;

	l = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '\n' && map[i][j] != arr[0]
					&& map[i][j] != arr[1])
				return (0);
			j++;
		}
		i++;
	}
	if (len != i)
		return (0);
	return (1);
}

int	check_line_lens_input(char **map, int len)
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

int	check_map_input(char **map, char *info)
{
	int		len;
	char	*arr;

	arr = get_info_input(info);
	len = line_count_input(info);
	if (!arr || len <= 0)
	{
		free(arr);
		return (0);
	}
	if (check_chars(map, arr, len) != 1)
	{
		free(arr);
		return (0);
	}
	if (check_line_lens_input(map, len) != 1)
	{
		free(arr);
		return (0);
	}
	free(arr);
	return (1);
}
