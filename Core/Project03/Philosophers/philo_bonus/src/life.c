/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:15:11 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/24 13:48:58 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (lock_forks(philo))
		return (1);
	print_message("is eating", philo, philo->id);
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_time();
	sem_post(philo->last_meal_sem);
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->meals_eaten);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (0);
}

int	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}
