/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:27:02 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/09 13:27:05 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_len(char *str, int i);

void	ft_error(char *str, int stop)
{
	write(1, str, ft_len(str, 0));
	write(1, "\n", 1);
	if (stop)
		exit(1);
}
