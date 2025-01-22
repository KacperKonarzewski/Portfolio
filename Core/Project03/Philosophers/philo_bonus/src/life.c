/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:15:11 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/21 22:27:48 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_stop);
	if (philo->data->dead_flag)
	{
		pthread_mutex_unlock(&philo->data->dead_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_stop);
	return (0);
}

int	lock_forks(t_philo *philo)
{
	if (philo->data->philos == 1)
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo, philo->id);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	if (lock_forks(philo))
		return (1);
	if (check_status(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating_flag = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating_flag = 0;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
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
