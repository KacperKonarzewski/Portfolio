/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:20:28 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:17:27 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ft_parse_primary(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	if (!current)
		return (NULL);
	if (!ft_strcmp(current->value, "("))
		return (handle_parenthesis(tokens));
	return (handle_command(tokens));
}

t_ast	*ft_parse_expression(t_token **tokens)
{
	t_ast		*left;
	t_ast		*right;
	t_ast		*parent;
	t_node_type	op_type;

	left = ft_parse_primary(tokens);
	while (*tokens && (!ft_strcmp((*tokens)->value, "&&")
			|| !ft_strcmp((*tokens)->value, "||")))
	{
		if (!ft_strcmp((*tokens)->value, "&&"))
			op_type = AND;
		else
			op_type = OR;
		*tokens = (*tokens)->next;
		right = ft_parse_primary(tokens);
		parent = ft_new_ast_node(op_type, NULL);
		parent->left = left;
		parent->right = right;
		left = parent;
	}
	return (left);
}

void	ft_evaluate_ast(t_ast *node, t_env_var *envp, int *status)
{
	if (!node)
		return ;
	if (node->type == CMD)
		child(node->command, envp, status);
	else if (node->type == AND)
	{
		ft_evaluate_ast(node->left, envp, status);
		if (*status == 0)
			ft_evaluate_ast(node->right, envp, status);
	}
	else if (node->type == OR)
	{
		ft_evaluate_ast(node->left, envp, status);
		if (*status != 0)
			ft_evaluate_ast(node->right, envp, status);
	}
}

void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	ft_free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->command)
		free(node->command);
	ft_free_ast(node->left);
	ft_free_ast(node->right);
	free(node);
}
