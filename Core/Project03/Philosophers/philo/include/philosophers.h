/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:56:25 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/14 13:24:59 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# define _POSIX_C_SOURCE 200809L

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	useconds_t		cur_status_time;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	int				times_eaten;
	int				max_eat;
	int				status;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}		t_philo;

typedef struct s_table
{
	int				died;
	t_philo			*philos;
}		t_table;

int	ft_atoi(const char *nptr);

#endif
