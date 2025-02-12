/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:20:28 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/12 10:32:34 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************** TOKEN LINKED LIST ***************************** */

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

/* **************************** TOKENIZATION ******************************* */

static void	skip_spaces(char **ptr)
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

static char	*get_next_token(char **ptr)
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

t_token	*ft_tokenize(char *cmd)
{
	t_token	*tokens;
	char	*token_value;
	char	*ptr;

	tokens = NULL;
	ptr = cmd;
	while (*ptr)
	{
		skip_spaces(&ptr);
		if (!*ptr)
			break ;
		token_value = get_next_token(&ptr);
		if (!token_value) /* unmatched quote or malloc fail */
			break ;
		ft_add_token(&tokens, token_value);
		free(token_value);
	}
	return (tokens);
}

/* *************************** AST CREATION ******************************* */

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

/* ********************** PARSING PRIMARIES ****************************** */

static t_ast	*handle_parenthesis(t_token **tokens)
{
	t_ast	*node;

	*tokens = (*tokens)->next; /* skip '(' */
	node = ft_parse_expression(tokens);
	if (*tokens && !ft_strcmp((*tokens)->value, ")"))
		*tokens = (*tokens)->next;
	else
		ft_putstr_fd("Syntax error: missing closing parenthesis\n", 2, -1);
	return (node);
}

static t_ast	*handle_command(t_token **tokens)
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

/* ********************** PARSING EXPRESSIONS ***************************** */

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

/* ************************ AST EVALUATION ******************************* */

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

/* *************************** FREEING *********************************** */

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

/* **************** MAIN LOGICAL OPERATOR PROCESSING ********************* */

void	process_logical_operators(char *cmd, t_env_var *envp, int *status)
{
	t_token	*tokens;
	t_token	*original_tokens;
	t_ast	*root;

	tokens = ft_tokenize(cmd);
	original_tokens = tokens;
	root = ft_parse_expression(&tokens);
	ft_evaluate_ast(root, envp, status);
	ft_free_tokens(original_tokens);
	ft_free_ast(root);
}
