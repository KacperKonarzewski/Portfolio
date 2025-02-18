/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:22:29 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/18 11:34:05 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_map_extension(char *map)
{
	size_t	len;
	int		fd;

	len = ft_strlen(map);
	if (len < 4 || ft_strncmp(map + len - 4, ".cub", 4) != 0)
		error(false, "Error!\nMap extension is wrong!");
	fd = open(map, O_RDONLY);
	if (fd == -1)
		error(true, NULL);
	return (fd);
}

void	init_vars(t_vars **vars, char *map)
{
	int		fd;
	char	*line;

	fd = check_map_extension(map);
}
