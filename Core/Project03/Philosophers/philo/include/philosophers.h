/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:56:25 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/13 20:48:34 by kkonarze         ###   ########.fr       */
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
	unsigned int	id;
	useconds_t		cur_status_time;
	int				status;
}		t_philo;

typedef struct s_table
{
	t_philo	*philos;
	int		*forks;
}		t_table;

typedef struct s_philo_data
{
	int			philos;
	useconds_t	time_to_die;
	useconds_t	time_to_eat;
	useconds_t	time_to_sleep;
	int			max_eat;
}		t_philo_data;

int	ft_atoi(const char *nptr);

#endif
