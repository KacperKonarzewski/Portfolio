/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:19:51 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/05 18:02:34 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_str(int size, char **strs, char *sep)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (i < size)
		len += ft_strlen(strs[i++]);
	len += ft_strlen(sep) * size - 1;
	if (size <= 0)
		len = 1;
	str = malloc(sizeof(char) * len);
	return (str);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*join;
	int		i;
	int		j;
	int		k;

	join = ft_str(size, strs, sep);
	k = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j])
			join[k++] = strs[i][j++];
		j = 0;
		while (sep[j] && i != size - 1)
			join[k++] = sep[j++];
		i++;
	}
	join[k] = '\0';
	return (join);
}
