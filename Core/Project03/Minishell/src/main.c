/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:51:53 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/03 14:45:21 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_text(char *text)
{
	char	cwd[PATH_MAX];

	if (!ft_strncmp(text, "exit", 5))
	{
		free(text);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strncmp(text, "pwd", 4))
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		return (1);
	}
	return (0);
}

void	main_loop(int original_stdin, int original_stdout, char **envp)
{
	char	*text;

	while (1)
	{
		text = readline("MiniAss 🍑>");
		if (!text)
			break ;
		add_history(text);
		if (handle_text(text))
		{
			free(text);
			continue ;
		}
		if (ft_strchr(text, '|'))
			manage_pipes(text, envp);
		else
			child(text, envp);
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		free(text);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int					original_stdin;
	int					original_stdout;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	main_loop(original_stdin, original_stdout, envp);
	close(original_stdin);
	close(original_stdout);
	return (0);
}
