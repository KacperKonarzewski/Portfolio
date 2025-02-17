/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:51:53 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/25 23:20:19 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

volatile int	g_ack_received = 0;

void	ack_handler(int sig)
{
	char	message_sent;

	message_sent = (sig == SIGUSR2);
	g_ack_received = 1;
	if (message_sent)
		ft_printf("Messege recieved\n");
}

void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		g_ack_received = 0;
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		while (!g_ack_received)
			usleep(1);
	}
}

void	send_message(pid_t server_pid, const char *message)
{
	while (*message)
		send_char(server_pid, *message++);
	send_char(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	char				*message;
	struct sigaction	sa;
	int					pid;

	if (argc != 3)
		return (0);
	pid = ft_atoi(argv[1]);
	message = argv[2];
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_message(pid, message);
	return (0);
}
