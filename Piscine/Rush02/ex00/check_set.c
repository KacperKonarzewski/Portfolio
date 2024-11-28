/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:07:21 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/08 23:07:39 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	search_lines(char *num, int argc, char **argv, int placement);

void	write_h(char *num, int argc, char **argv, int len)
{
	char	*current_line;

	current_line = malloc(3);
	current_line[2] = '\0';
	current_line[0] = num[0];
	current_line[1] = '\0';
	search_lines(current_line, argc, argv, len);
	len--;
	search_lines("100", argc, argv, len);
	free(current_line);
}

void	write_t(char *num, int argc, char **argv, int len)
{
	char	*current_line;

	current_line = malloc(3);
	current_line[2] = '\0';
	current_line[0] = num[1];
	current_line[1] = num[2];
	search_lines(current_line, argc, argv, len);
	free(current_line);
}

void	write_d(char *num, int argc, char **argv, int len)
{
	char	*current_line;

	current_line = malloc(3);
	current_line[2] = '\0';
	current_line[0] = num[1];
	current_line[1] = '0';
	search_lines(current_line, argc, argv, len);
	free(current_line);
}

void	write_l(char *num, int argc, char **argv, int len)
{
	char	*current_line;

	current_line = malloc(3);
	current_line[2] = '\0';
	current_line[0] = num[2];
	current_line[1] = '\0';
	search_lines(current_line, argc, argv, len);
	free(current_line);
}

void	print_thousand(int len, int argc, char **argv)
{
	int		i;
	char	*current_line;

	current_line = malloc(len + 1);
	current_line[0] = '1';
	i = 1;
	printf("%d", len);
	while (i < len)
	{
		current_line[i] = '0';
		i++;
	}
	current_line[i] = '\0';
	search_lines(current_line, argc, argv, len);
	free(current_line);
}
