/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:05:03 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/21 17:24:46 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table			table;
	int				i;
	t_data			data;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_data(argc, argv, &data) != 0)
		return (0);
	if (init_table(&data, &table) != 0)
		return (0);
	if (start_philos(&data, &table) != 0)
		return (0);
	clean_up(&table, data.philos, 0);
	free(table.forks);
	i = -1;
	while (++i < data.philos)
		pthread_mutex_destroy(&table.philos[i].meal_lock);
	free(table.philos);
}
