/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:12:05 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:12:25 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
