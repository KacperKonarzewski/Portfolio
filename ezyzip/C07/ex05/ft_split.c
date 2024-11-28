/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 23:49:45 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/10 03:24:14 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	find_sep(char *charset, char c)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

int	amount_of_strings(char *str, char *charset)
{
	int	i;
	int	ctr;

	i = -1;
	ctr = 0;
	while (str[++i])
		if (!find_sep(charset, str[i]) && (find_sep(charset, str[i + 1])
				|| str[i + 1] == '\0'))
			ctr++;
	return (ctr);
}

void	put_values(char **strs, int maxi, char *str, char *charset)
{
	int	i;
	int	j;
	int	k;
	int	length;

	i = -1;
	j = 0;
	while (++i < maxi)
	{
		while (str[j] && find_sep(charset, str[j]))
			j++;
		length = 0;
		while (str[j] && !find_sep(charset, str[j]))
		{
			length++;
			j++;
		}
		strs[i] = (char *)malloc(sizeof(char) * (length + 1));
		k = 0;
		while (length-- > 0)
			strs[i][k++] = str[j - length - 1];
		strs[i][k] = '\0';
		while (str[j] && find_sep(charset, str[j]))
			j++;
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**strs;
	int		i;

	i = amount_of_strings(str, charset);
	strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	put_values(strs, i, str, charset);
	strs[i] = 0;
	return (strs);
}
