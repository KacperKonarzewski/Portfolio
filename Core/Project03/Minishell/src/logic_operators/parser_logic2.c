/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:10:23 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:14:31 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **head, const char *value)
{
	t_token	*token;
	t_token	*current;

	token = ft_new_token(value);
	if (!*head)
		*head = token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = token;
	}
}

t_ast	*ft_new_ast_node(t_node_type type, char *command)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	if (command)
		node->command = ft_strdup(command);
	else
		node->command = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*handle_parenthesis(t_token **tokens)
{
	t_ast	*node;

	*tokens = (*tokens)->next;
	node = ft_parse_expression(tokens);
	if (*tokens && !ft_strcmp((*tokens)->value, ")"))
		*tokens = (*tokens)->next;
	else
		ft_putstr_fd("Syntax error: missing closing parenthesis\n", 2, -1);
	return (node);
}

t_ast	*handle_command(t_token **tokens)
{
	t_ast	*node;
	char	*command;
	char	*temp;
	t_token	*cur;

	cur = *tokens;
	command = ft_strdup(cur->value);
	*tokens = cur->next;
	while (*tokens && ft_strcmp((*tokens)->value, "&&")
		&& ft_strcmp((*tokens)->value, "||")
		&& ft_strcmp((*tokens)->value, ")"))
	{
		temp = ft_strjoin(command, " ");
		free(command);
		command = ft_strjoin(temp, (*tokens)->value);
		free(temp);
		*tokens = (*tokens)->next;
	}
	node = ft_new_ast_node(CMD, command);
	free(command);
	return (node);
}
