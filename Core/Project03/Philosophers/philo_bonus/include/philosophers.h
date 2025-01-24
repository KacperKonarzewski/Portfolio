/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:11:38 by mbari             #+#    #+#             */
/*   Updated: 2025/01/24 14:24:19 by kkonarze         ###   ########.fr       */
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
# include <sys/wait.h>
# include <signal.h>

struct	s_philo;

typedef struct s_simulation
{
	sem_t			*forks;
	sem_t			*message;
	sem_t			*death;
	sem_t			*meals_eaten;
	sem_t			*finish;
	struct s_philo	*all_philos;
	pthread_t		monitor;
	size_t			start;
	int				is_dead;
	int				philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
}				t_simulation;

typedef struct s_philo
{
	t_simulation	*data;
	pthread_t		monitor;
	sem_t			*last_meal_sem;
	char			*sem_name;
	pid_t			pid;
	int				eating_flag;
	size_t			last_meal;
	int				id;
	int				meals_eaten;
}				t_philo;

void	*check_if_dead(void *ptr);
void	*check_if_all_ate(void *ptr);
void	create_semaphore(t_philo *philo, int n);
void	print_message(char *str, t_philo *philo, int id);
size_t	get_time(void);
int		ft_usleep(size_t time);
void	clean_up(t_simulation *sim, int parent, int signal);
int		init_data(int argc, char **argv, t_simulation *data);
void	init_philo(t_simulation *data);
int		eat(t_philo *philo);
long	ft_atol(const char *nptr);
int		dream(t_philo *philo);

#endif
