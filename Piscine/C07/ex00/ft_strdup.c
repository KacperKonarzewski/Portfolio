/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:56:18 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/04 21:33:47 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	get_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (++i);
}

char	*ft_strdup(char *src)
{
	char	*strdup;
	int		i;

	i = -1;
	strdup = (char *)malloc(get_size(src));
	if (strdup != NULL)
	{
		while (src[++i])
			strdup[i] = src[i];
		strdup[i] = '\0';
	}
	return (strdup);
}
