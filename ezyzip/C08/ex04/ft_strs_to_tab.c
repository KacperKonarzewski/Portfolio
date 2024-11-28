/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 06:24:01 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/12 01:38:50 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stock_str.h"

int	ft_strlen(char *str, int i)
{
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*strdup;
	int		i;

	i = -1;
	strdup = (char *)malloc(ft_strlen(src, 0) + 1);
	if (strdup != NULL)
	{
		while (src[++i])
			strdup[i] = src[i];
		strdup[i] = '\0';
	}
	return (strdup);
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	t_stock_str	*tab;
	int			i;

	tab = malloc(sizeof(t_stock_str) * (ac + 1));
	if (tab == NULL)
		return (NULL);
	i = -1;
	while (++i < ac)
	{
		tab[i].str = av[i];
		tab[i].copy = ft_strdup(av[i]);
		tab[i].size = ft_strlen(av[i], 0);
	}
	tab[i].str = 0;
	return (tab);
}
