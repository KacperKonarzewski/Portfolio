/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:05:03 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/24 14:15:22 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;
	int		cpy;

	cpy = n;
	digits = 0;
	while (cpy / 10 != 0)
	{
		digits += 1;
		cpy /= 10;
	}
	str = (char *)malloc(((n < 0) + digits + 2) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[(n < 0) + digits + 1] = 0;
	while (digits + (n < 0) >= (n < 0))
	{
		str[digits-- + (n < 0)] = (n % 10 * ((n > 0) - (n < 0))) + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

void	create_semaphore(t_philo *philo, int n)
{
	char	*temp;

	temp = ft_itoa(n);
	philo->sem_name = ft_strjoin("last_meal_", temp);
	free(temp);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	sem_unlink("/last_meal_sem");
	if (argc != 5 && argc != 6)
		return (0);
	if (init_data(argc, argv, &sim) != 0)
		return (0);
	init_philo(&sim);
	sem_wait(sim.finish);
	clean_up(&sim, 1, EXIT_SUCCESS);
}
