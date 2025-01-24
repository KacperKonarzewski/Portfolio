/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:50:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/24 14:25:13 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	sem_wait(philo->data->message);
	time = get_time() - philo->data->start;
	printf("%zums %d %s\n", time, id, str);
	sem_post(philo->data->message);
}

void	*check_if_dead(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->last_meal_sem);
		if (get_time() - philo->last_meal > philo->data->time_to_die)
		{
			print_message("died", philo, philo->id);
			sem_post(philo->data->finish);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->last_meal_sem);
		ft_usleep(1);
	}
	return (0);
}

void	*check_if_all_ate(void *ptr)
{
	int				finished_eating;
	t_simulation	*sim;

	finished_eating = 0;
	sim = (t_simulation *)ptr;
	if (sim->philos == 1)
	{
		sem_post(sim->death);
		return (NULL);
	}
	while (sim->max_eat != -1)
	{
		sem_wait(sim->meals_eaten);
		++finished_eating;
		if (finished_eating >= sim->max_eat * sim->philos)
		{
			sem_post(sim->death);
			sem_post(sim->finish);
			return (NULL);
		}
	}
	sem_post(sim->death);
	return (NULL);
}
