/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:25:22 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/23 14:37:24 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_life(t_philo philo)
{
	if (pthread_create(&philo.monitor, NULL, monitor, philo) \
		!= 0)
		return ;
	pthread_detach(&philos[i].monitor);
	if (philo.id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if (eat(philo) != 0)
			break ;
		if (dream(philo) != 0)
			break ;
		if (check_status(philo))
			break ;
		print_message("is thinking", philo, philo.id);
	}
	return (philo);
}

void	start_philos(t_philo *philos)
{
	int		i;
	pid_t	pid;
	void	*result;

	i = 0;
	philos[0].data->start = get_time();
	if (pthread_create(&philos[i].monitor, NULL, monitor, philos) \
		!= 0)
		return ;
	pthread_detach(&philos[i].monitor);
	while (i < philos->data->philos)
	{
		pid = fork();
		if (pid < 0)
			return ;
		philos[i].pid = pid;
		if (pid == 0)
			start_life(philos[i]);
		i++;
	}
	while (--i >= 0)
		waitpid(philos[i], NULL, 0);
}

void	init_philo(t_simulation *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(data->philos * sizeof(t_philo));
	i = 0;
	while (i < data->philos)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_time();
	}
	data->all_philos = philo;
	start_philos(philo);
}

int	init_data(int argc, char **argv, t_simulation *data)
{
	int	i;

	i = 1;
	while (i < argc)
		if (ft_atol(argv[i++]) <= 0)
			return (1);
	if (ft_atol(argv[1]) > 200)
		return (2);
	data->is_dead = 0;
	data->philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atol(argv[5]);
	else
		data->max_eat = -1;
	if (init_semaphores(data))
		return (3);
	return (0);
}

int	init_semaphores(t_simulation *sim)
{
	sim->forks = sem_open("forks", O_CREAT | O_EXCL, 0666, sim->philos);
	sim->message = sem_open("message", O_CREAT | O_EXCL, 0666, 1);
	sim->death = sem_open("death", O_CREAT | O_EXCL, 0666, sim->philos);
	if (sim->forks == SEM_FAILED || sim->message == SEM_FAILED
		|| sim->death == SEM_FAILED)
		return (1);
	return (0);
}
