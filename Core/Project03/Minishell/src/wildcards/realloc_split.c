/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:40:58 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:04:10 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_after_i(char **splitted, int i)
{
	int	remainder;

	remainder = 0;
	while (splitted[i + 1 + remainder])
		remainder++;
	return (remainder);
}

static void	ft_copy_before_i(char **dst, char **src, int i)
{
	int	x;

	x = 0;
	while (x < i)
	{
		dst[x] = src[x];
		x++;
	}
}

static void	ft_copy_expanded(char **dst, char **expanded, int start)
{
	int	x;

	x = 0;
	while (expanded[x])
	{
		dst[start + x] = expanded[x];
		x++;
	}
}

static void	ft_copy_after_i(char **dst, char **src, int i, int offset)
{
	int	x;

	x = 0;
	while (src[i + 1 + x])
	{
		dst[offset + x] = src[i + 1 + x];
		x++;
	}
	dst[offset + x] = NULL;
}

void	realloc_split(char ***splitted, char **expanded, int i)
{
	char	**tmp;
	int		remainder;
	int		k;
	int		new_size;

	remainder = ft_count_after_i(*splitted, i);
	k = 0;
	while (expanded[k])
		k++;
	new_size = i + k + remainder + 1;
	tmp = malloc(new_size * sizeof(char *));
	if (!tmp)
		return ;
	ft_copy_before_i(tmp, *splitted, i);
	ft_copy_expanded(tmp, expanded, i);
	ft_copy_after_i(tmp, *splitted, i, i + k);
	free(*splitted);
	*splitted = tmp;
}
