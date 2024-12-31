/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:05:21 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/02 00:13:53 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoined;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	strjoined = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!strjoined)
		return (NULL);
	while (i < s1_len)
	{
		strjoined[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		strjoined[s1_len + i] = s2[i];
		i++;
	}
	strjoined[s1_len + s2_len] = 0;
	return (strjoined);
}
