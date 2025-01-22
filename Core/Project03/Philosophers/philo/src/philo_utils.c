/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:57:58 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/20 14:49:06 by kkonarze         ###   ########.fr       */
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

int	clean_up(t_table *table, int len, int error)
{
	int	i;

	i = 0;
	while (i < len)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->philos[0].data->dead_stop);
	pthread_mutex_destroy(&table->philos[0].data->write_lock);
	return (error);
}
