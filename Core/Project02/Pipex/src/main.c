/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:51:53 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/04 23:47:22 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error(1, "");
	pid = fork();
	if (pid == -1)
		error(1, "");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		use_cmd(cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	handle_hear_doc(char *limiter, int argc)
{
	pid_t	line_reader;
	int		fd[2];
	char	*line;

	if (argc < 6 || pipe(fd) == -1)
		error(0, "Error, wrong hear_doc input or pipe creation!");
	line_reader = fork();
	if (line_reader == 0)
	{
		close(fd[0]);
		while (get_input(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		fileout;
	int		filein;

	if (argc < 4)
		error(0, "Error, wrong input!\nCorrect input: \
./pipex infile cmd1 cmd2 ... cmdn outfile");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 2;
		fileout = file_opener(argv[argc - 1], 2);
		handle_hear_doc(argv[2], argc);
	}
	else
	{
		i = 1;
		filein = file_opener(argv[1], 0);
		fileout = file_opener(argv[argc - 1], 1);
		dup2(filein, STDIN_FILENO);
	}
	while (++i < argc - 2)
		child(argv[i], envp);
	dup2(fileout, STDOUT_FILENO);
	use_cmd(argv[argc - 2], envp);
	return (0);
}
