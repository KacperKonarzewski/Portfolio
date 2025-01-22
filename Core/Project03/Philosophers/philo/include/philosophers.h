/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:56:25 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/21 18:27:07 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <pthread.h>

typedef struct s_data
{
	int				philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			started;
	int				amount_meals;
	pthread_mutex_t	dead_stop;
	pthread_mutex_t	write_lock;
	int				dead_flag;
}					t_data;

struct	s_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
	pthread_t		monitor;
}					t_table;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	int				eating_flag;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	meal_lock;
	struct s_data	*data;
	struct s_table	*table;
}					t_philo;

long	ft_atol(const char *nptr);
int		clean_up(t_table *table, int len, int error);
int		init_table(t_data *data, t_table *table);
size_t	get_time(void);
int		ft_usleep(size_t time);
int		init_data(int argc, char **argv, t_data *data);
int		start_philos(t_data *data, t_table *table);
void	print_message(char *str, t_philo *philo, int id);
int		check_status(t_philo *philo);
int		eat(t_philo *philo);
int		dream(t_philo *philo);
void	*monitor(void *arg);

#endif
