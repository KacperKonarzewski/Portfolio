/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:56:22 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/04 02:58:15 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	char	*str;

	i = 1;
	while (++i < argc)
	{
		str = argv[i];
		j = i;
		while (j > 0 && ft_strcmp(str, argv[j - 1]) < 0)
		{
			argv[j] = argv[j - 1];
			j--;
		}
		argv[j] = str;
	}
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != '\0')
			write(1, &argv[i][j], 1);
		write(1, "\n", 1);
	}
	return (0);
}
