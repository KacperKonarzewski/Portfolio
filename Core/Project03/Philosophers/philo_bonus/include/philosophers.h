/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:38 by mbari             #+#    #+#             */
/*   Updated: 2025/01/23 14:24:18 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

typedef	t_philo;

typedef struct s_simulation
{
	sem_t	*forks;
	sem_t	*message;
	sem_t	*death;
	sem_t	*meals_eaten;
	t_philo	*all_philos;
	size_t	start;
	int		is_dead;
	int		philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_eat;
}				t_simulation;

typedef struct s_philo
{
	t_simulation	*data;
	pthread_t		monitor;
	pid_t			pid;
	int				eating_flag;
	size_t			last_meal;
	int				id;
	int				meals_eaten;
}				t_philo;

void	*monitor(void *pointer);
void	print_message(char *str, t_philo *philo, int id);

#endif
