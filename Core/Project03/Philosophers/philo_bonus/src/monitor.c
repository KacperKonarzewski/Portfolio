/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:50:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/23 14:40:59 by kkonarze         ###   ########.fr       */
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

void	*check_if_dead(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->data->death);
		if (get_current_time() - philo->times.last_meal > philo->times.die)
		{
			//print_action(philo, RED"died"RESET);
			sem_wait(philo->sems->write_sem);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->sems->die_sem);
		ft_sleep(1);
	}
	return (0);
}

void	*check_if_all_ate(void *ptr)
{
	int				i;
	int				finished_eating;
	t_simulation	*sim;

	i = 0;
	finished_eating = 0;
	sim = (t_simulation *)ptr;
	while (1)
	{
		sem_wait(sim->meals_eaten);
		++finished_eating;
		if (finished_eating >= sim->philos)
			destroy_all(sim, NULL, 1, EXIT_SUCCESS);
		ft_sleep(1);
	}
	return (NULL);
}
