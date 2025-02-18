/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:35:18 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/18 08:36:37 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **splitted)
{
	int	i;

	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
}
