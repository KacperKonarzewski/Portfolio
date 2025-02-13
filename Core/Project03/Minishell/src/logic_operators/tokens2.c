/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:15:51 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:16:13 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!token_value)
			break ;
		ft_add_token(&tokens, token_value);
		free(token_value);
	}
	return (tokens);
}
