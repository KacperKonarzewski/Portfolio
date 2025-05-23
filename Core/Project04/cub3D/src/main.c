/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:38:18 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/19 13:44:42 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		error(false, "Error!\nWrong amount of arguments");
	init_vars(&vars, argv[1]);
}
