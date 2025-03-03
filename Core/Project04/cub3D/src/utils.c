/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacper <kacper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:19:55 by kkonarze          #+#    #+#             */
/*   Updated: 2025/03/02 19:41:41 by kacper           ###   ########.fr       */
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
		printf("Error!\n%s\n", message);
		exit(0);
	}
}
