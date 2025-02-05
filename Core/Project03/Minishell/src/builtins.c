/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:27:08 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/05 12:00:05 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (0);
	printf("%s\n", cwd);
	return (1);
}

int	ft_cd(char *text)
{
	chdir(text);
	return (1);
}

int	ft_echo(char **text, t_env_var *envp, int *status)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 0;
	if (!ft_strncmp(text[1], "-n", 3))
	{
		new_line = 1;
		i = 2;
	}
	handle_special(text, envp, 0, status);
	while (text[i])
	{
		if (check_redirections(text, i))
			continue ;
		printf("%s", text[i]);
		if (text[i + 1])
			printf(" ");
		i++;
	}
	if (!new_line)
		printf("\n");
	return (1);
}
