/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:51:53 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/03 19:40:09 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	character = 0;

	(void)context;
	character |= (sig == SIGUSR2);
	bit_count++;
	if (bit_count == 8)
	{
		if (character == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
			write(1, &character, 1);
		bit_count = 0;
		character = 0;
	}
	else
		character <<= 1;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%d\n", getpid());
	while (1)
		;
	return (0);
}
