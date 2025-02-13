/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:03:06 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:03:58 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_wildcards(char ***splitted, int i)
{
	char	*expanded_str;
	char	**expanded_arr;

	if (ft_strchr((*splitted)[i], '*'))
	{
		expanded_str = expand_wildcards((*splitted)[i]);
		expanded_arr = ft_split_quotes(expanded_str, " ");
		free(expanded_str);
		if (!expanded_arr || !expanded_arr[0])
		{
			free(expanded_arr);
			return ;
		}
		realloc_split(splitted, expanded_arr, i);
	}
}
