/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:50:54 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/02 13:38:38 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	amount_of_strings(const char *str, char c)
{
	int	i;
	int	ctr;

	i = -1;
	ctr = 0;
	while (str[++i])
		if (!(str[i] == c) && (str[i + 1] == c
				|| str[i + 1] == '\0'))
			ctr++;
	return (ctr);
}

static void	put_values(char **strs, int maxi, const char *str, char c)
{
	int	i;
	int	j;
	int	k;
	int	length;

	i = -1;
	j = 0;
	while (++i < maxi)
	{
		while (str[j] && str[j] == c)
			j++;
		length = 0;
		while (str[j] && !(str[j] == c))
		{
			length++;
			j++;
		}
		strs[i] = (char *)malloc(sizeof(char) * (length + 1));
		k = 0;
		while (length-- > 0)
			strs[i][k++] = str[j - length - 1];
		strs[i][k] = '\0';
		while (str[j] && str[j] == c)
			j++;
	}
}

char	**ft_split(const char *s, char c)
{
	char	**strs;
	int		i;

	i = amount_of_strings(s, c);
	strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	put_values(strs, i, s, c);
	strs[i] = 0;
	return (strs);
}
