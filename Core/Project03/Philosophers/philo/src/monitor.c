/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:50:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/21 22:29:38 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time() - philo->data->started;
	if (check_status(philo) == 0)
		printf("%zums %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time() - philo->last_meal >= time_to_die + 1
		&& philo->eating_flag == 0)
		return (pthread_mutex_unlock(&philo->meal_lock), 1);
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->philos)
	{
		if (philosopher_dead(&philos[i], philos[i].data->time_to_die))
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(&philos[0].data->dead_stop);
			philos->data->dead_flag = 1;
			pthread_mutex_unlock(&philos[0].data->dead_stop);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].data->amount_meals == -1)
		return (0);
	while (i < philos[0].data->philos)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].data->amount_meals)
			finished_eating++;
		pthread_mutex_unlock(&philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].data->philos)
	{
		pthread_mutex_lock(&philos[0].data->dead_stop);
		philos->data->dead_flag = 1;
		pthread_mutex_unlock(&philos[0].data->dead_stop);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_if_dead(philos) == 1)
			break ;
		if (check_if_all_ate(philos) == 1)
			break ;
		ft_usleep(1);
	}
	return (pointer);
}
