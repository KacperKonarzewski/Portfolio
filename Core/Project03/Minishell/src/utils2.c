/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:20:41 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/05 23:20:57 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_sep(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	amount_of_strings(char *str, char *charset)
{
	int	i;
	int	ctr;
	int	single_q;
	int	double_q;

	i = -1;
	ctr = 0;
	single_q = 0;
	double_q = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && double_q == 0)
			single_q = !single_q;
		else if (str[i] == '\"' && single_q == 0)
			double_q = !double_q;
		if (str[i] == '\'' && single_q == 0 && double_q == 0)
			ctr++;
		else if (str[i] == '\"' && double_q == 0 && single_q == 0)
			ctr++;
		else if (!find_sep(charset, str[i])
			&& (find_sep(charset, str[i + 1]) || str[i + 1] == '\0')
			&& single_q == 0 && double_q == 0)
			ctr++;
	}
	return (ctr);
}

static char	*copy_str_quotes(const char *str, int start, int end)
{
	char	*ret;
	int		i;
	int		j;

	if (str[end] == '\'' || str[end] == '\"')
		end++;
	ret = malloc(sizeof(char) * (end - start + 1));
	if (!ret)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
	{
		ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

static void	put_values(char **strs, int maxi, char *str, char *charset)
{
	int	i[2];
	int	start;
	int	q[2];

	i[0] = 0;
	i[1] = 0;
	while (i[0] < maxi)
	{
		q[0] = 0;
		q[1] = 0;
		while (str[i[1]] && find_sep(charset, str[i[1]]) && !q[0] && !q[1])
			i[1]++;
		start = i[1];
		while (str[i[1]++])
		{
			if (str[i[1] - 1] == '\'' && q[1] == 0)
				q[0] = !q[0];
			else if (str[i[1] - 1] == '\"' && q[0] == 0)
				q[1] = !q[1];
			if (!q[0] && !q[1] && (find_sep(charset, str[i[1] - 1]) \
				|| str[i[1] - 1] == '\'' || str[i[1] - 1] == '\"'))
				break ;
		}
		strs[i[0]++] = copy_str_quotes(str, start, i[1] - 1);
	}
}

char	**ft_split_quotes(char *cmd, char *set)
{
	char	**strs;
	int		count;

	count = amount_of_strings(cmd, set);
	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	strs[count] = NULL;
	put_values(strs, count, cmd, set);
	return (strs);
}
