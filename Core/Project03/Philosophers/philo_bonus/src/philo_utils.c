/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:58 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/24 14:24:57 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9') * c);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

long	ft_atol(const char *nptr)
{
	long		count;
	int			i;
	int			is_negative;

	i = 0;
	count = 0;
	is_negative = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if ((nptr[i] == '-' || nptr[i] == '+') && ++i)
		is_negative = (nptr[i - 1] == '+') - (nptr[i - 1] == '-');
	while (nptr[i] && ft_isdigit(nptr[i]))
		count = (count * 10) + ((nptr[i++] - 48) * is_negative);
	return (count);
}

void	clean_up(t_simulation *sim, int parent, int signal)
{
	int	i;

	i = -1;
	if (parent)
		while (++i < sim->philos)
			if (sim->all_philos[i].pid != -1)
				kill(sim->all_philos[i].pid, SIGKILL);
	i = -1;
	while (++i <= sim->max_eat * sim->philos)
		sem_post(sim->meals_eaten);
	i = -1;
	while (++i < sim->philos)
	{
		sem_close(sim->all_philos[i].last_meal_sem);
		free(sim->all_philos[i].sem_name);
	}
	sem_wait(sim->death);
	ft_usleep(100);
	sem_close(sim->forks);
	sem_close(sim->death);
	sem_close(sim->meals_eaten);
	sem_close(sim->message);
	sem_close(sim->finish);
	free(sim->all_philos);
	exit(signal);
}
