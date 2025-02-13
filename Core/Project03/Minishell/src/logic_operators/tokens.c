/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:06:33 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:30:08 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **ptr)
{
	while (**ptr && **ptr == ' ')
		(*ptr)++;
}

static int	is_logical_op(const char *str)
{
	if (!ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2))
		return (1);
	return (0);
}

static char	*extract_quoted(char **ptr)
{
	char	quote;
	char	*start;
	char	*token_value;

	quote = **ptr;
	(*ptr)++;
	start = *ptr;
	while (**ptr && **ptr != quote)
		(*ptr)++;
	if (**ptr == quote)
	{
		token_value = ft_substr(start, 0, (*ptr) - start);
		(*ptr)++;
	}
	else
	{
		ft_putstr_fd("Syntax error: unmatched quote\n", 2, -1);
		token_value = NULL;
	}
	return (token_value);
}

static char	*extract_word(char **ptr)
{
	char	*start;
	char	*token_value;

	start = *ptr;
	while (**ptr && **ptr != ' ' && !is_logical_op(*ptr)
		&& **ptr != '(' && **ptr != ')' && **ptr != '\'' && **ptr != '\"')
	{
		(*ptr)++;
	}
	token_value = ft_substr(start, 0, (*ptr) - start);
	return (token_value);
}

char	*get_next_token(char **ptr)
{
	char	symbol[3];

	skip_spaces(ptr);
	if (!**ptr)
		return (NULL);
	if (**ptr == '(' || **ptr == ')')
	{
		symbol[0] = **ptr;
		symbol[1] = '\0';
		(*ptr)++;
		return (ft_strdup(symbol));
	}
	else if (is_logical_op(*ptr))
	{
		symbol[0] = **ptr;
		symbol[1] = *(*ptr + 1);
		symbol[2] = '\0';
		(*ptr) += 2;
		return (ft_strdup(symbol));
	}
	else if (**ptr == '\'' || **ptr == '\"')
		return (extract_quoted(ptr));
	return (extract_word(ptr));
}
