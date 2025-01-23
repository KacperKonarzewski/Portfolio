/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:15:11 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/23 13:59:56 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_status(t_philo *philo)
{
	sem_wait(philo->data->death);
	if (get_time() - philo->last_meal >= philo->data->time_to_die + 1
		&& philo->eating_flag == 0)
		
	sem_post(philo->data->death);
	return (0);
}

int	lock_forks(t_philo *philo)
{
	if (philo->data->philos == 1)
		return (1);
	sem_wait(philo->data->forks);
	print_message("has taken a fork", philo, philo->id);
	sem_wait(philo->data->forks);
	print_message("has taken a fork", philo, philo->id);
	return (0);
}

int	eat(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	if (lock_forks(philo))
		return (1);
	check_status(philo);
	print_message("is eating", philo, philo->id);
	philo->last_meal = get_time();

	ft_usleep(philo->data->time_to_eat);

	philo->eating_flag = 0;
	philo->meals_eaten++;

	return (0);
}

int	dream(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}
