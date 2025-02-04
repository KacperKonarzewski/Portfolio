/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:51:53 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/04 14:45:53 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_before(char *text)
{
	char	**splitted;

	splitted = ft_split(text, " ");
	if (!ft_strncmp(splitted[0], "exit", 5))
		exit(EXIT_SUCCESS);
	else if (!ft_strncmp(splitted[0], "cd", 2))
	{
		ft_cd(splitted[1]);
		free_split(splitted);
		return (1);
	}
	free_split(splitted);
	return (0);
}

int	handle_text(char **text, t_env_var *envp)
{
	if (!ft_strncmp(text[0], "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(text[0], "env", 4))
		return (print_env_vars(envp));
	else if (!ft_strncmp(text[0], "echo", 5))
		return (ft_echo(text));
	return (0);
}

void	main_loop(int original_stdin, int original_stdout, t_env_var *envp)
{
	char	*text;

	while (1)
	{
		text = readline("MiniAss 🍑>");
		if (!text)
			break ;
		add_history(text);
		if (handle_before(text))
			continue ;
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
	t_env_var			*list;

	(void)argc;
	(void)argv;
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	envp_to_list(&list, envp);
	main_loop(original_stdin, original_stdout, list);
	close(original_stdin);
	close(original_stdout);
	return (0);
}
