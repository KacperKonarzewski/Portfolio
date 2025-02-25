/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:25:22 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/23 21:26:16 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if (eat(philo) != 0)
			break ;
		if (dream(philo) != 0)
			break ;
		if (check_status(philo))
			break ;
		print_message("is thinking", philo, philo->id);
	}
	return ((void *)philo);
}

int	start_philos(t_data *data, t_table *table)
{
	int		i;
	void	*result;

	i = 0;
	data->started = get_time();
	while (i < data->philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, start_life, \
			&table->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&table->monitor, NULL, monitor, &table->philos[0]) != 0)
		return (1);
	while (--i >= 0)
		if (pthread_join(table->philos[i].thread, &result) != 0)
			return (1);
	if (pthread_join(table->monitor, NULL) != 0)
		return (1);
	return (0);
}

void	init_philo(t_data *data, t_table *table, int i)
{
	t_philo	philo;

	philo.id = i + 1;
	philo.meals_eaten = 0;
	philo.data = data;
	philo.table = table;
	philo.last_meal = get_time();
	philo.eating_flag = 0;
	philo.r_fork = &table->forks[(i + 1) * (i + 1 < data->philos)];
	philo.l_fork = &table->forks[i];
	pthread_mutex_init(&philo.meal_lock, NULL);
	table->philos[i] = philo;
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (i < argc)
		if (ft_atol(argv[i++]) <= 0)
			return (1);
	if (ft_atol(argv[1]) > 200)
		return (2);
	data->dead_flag = 0;
	if (pthread_mutex_init(&data->dead_stop, NULL) != 0)
		return (3);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (3);
	data->philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->amount_meals = ft_atol(argv[5]);
	else
		data->amount_meals = -1;
	return (0);
}

int	init_table(t_data *data, t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(data->philos * sizeof(t_philo));
	if (!table->philos)
		return (1);
	table->forks = malloc(data->philos * sizeof(pthread_mutex_t));
	if (!table->forks)
	{
		free(table->philos);
		return (1);
	}
	while (i < data->philos)
		if (pthread_mutex_init(&table->forks[i++], NULL) != 0)
			return (clean_up(table, i, 2));
	i = 0;
	while (i < data->philos)
		init_philo(data, table, i++);
	return (0);
}
