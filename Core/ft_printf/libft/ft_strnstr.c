/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:11:49 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/05 08:47:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;
	size_t	count;

	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	count = 0;
	while (i < len && big[i] && little[count])
	{
		if (big[i] == little[count])
			count++;
		else
		{
			i -= count;
			count = 0;
		}
		i++;
	}
	if (little_len == count)
		return ((char *)&big[i - count]);
	return (0);
}
