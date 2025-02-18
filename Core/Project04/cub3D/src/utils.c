/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:19:55 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/18 09:57:50 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error(bool type, char *message)
{
	if (type)
	{
		printf("Error\n%s", strerror(errno));
		exit(0);
	}
	else
	{
		printf("%s\n", message);
		exit(0);
	}
}
