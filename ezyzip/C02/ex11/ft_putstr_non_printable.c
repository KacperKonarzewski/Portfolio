/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:35:52 by kkonarze          #+#    #+#             */
/*   Updated: 2024/08/27 15:43:57 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	write_hex(char	*c)
{
	int		i;
	char	*hexes;

	hexes = "0123456789abcdef";
	i = *c;
	if (i < 0)
	{
		i = i + 256;
	}
	write(1, "\\", 1);
	write(1, &hexes[i / 16], 1);
	write(1, &hexes[i % 16], 1);
}

void	ft_putstr_non_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < ' ' || str[i] < '~')
		{
			write_hex(&str[i]);
		}
		else
		{
			write(1, &str[i], 1);
		}
		i++;
	}
}
