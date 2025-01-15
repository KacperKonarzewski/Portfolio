/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:05:03 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/15 22:32:04 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_table	init_table(t_philo_data *data)
{
	t_table	table;

	table.philos = malloc(data->philos * sizeof(t_philo));
	table.forks = malloc(data->philos * sizeof(int));
	if (!table.philos || !table.philos)
		return (table);
	
	return (table);
}

t_philo_data	init_data(int argc, char **argv)
{
	t_philo_data	data;

	data.philos = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.max_eat = ft_atoi(argv[5]);
	else
		data.max_eat = -1;
	return (data);
}

int	main(int argc, char **argv)
{
	t_philo_data	data;
	t_table			table;

	if (argc < 5)
		return (0);
	data = init_data(argc, argv);

}
