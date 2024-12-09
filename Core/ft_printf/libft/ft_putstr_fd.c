/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:33:43 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/09 22:07:11 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
	return (i);
}
