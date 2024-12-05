/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:09:02 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/05 08:48:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned char		chr;

	src = (const unsigned char *)s;
	chr = (unsigned char)c;
	while (n--)
	{
		if (*src == chr)
			return ((void *)src);
		src++;
	}
	return (0);
}
