/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:14:44 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/05 14:38:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	find_zero_context(const char *str)
{
	int	i;
	int	found;

	found = 0;
	i = -1;
	while (str[++i] && i < 5)
	{
		if (ft_isdigit(str[i]) && found)
			return (1);
		else if (ft_isdigit(str[i]) > '0')
			return (0);
		else if (str[i] == '0')
			found = 1;
	}
	return (1);
}

static void	find_modi(const char *str, size_t len, char *cur)
{
	int	i;

	i = 0;
	if ((str[len - 1] == 'x' || str[len - 1] == 'X')
		&& find_in_set('#', str) != 0)
		cur[i++] = '#';
	if (find_in_set(' ', str) != 0 && find_in_set('+', str) == 0
		&& (str[len - 1] == 'i' || str[len - 1] == 'd' || str[len - 1] == 'u'))
		cur[i++] = ' ';
	if (find_in_set('+', str) != 0 && (str[len - 1] == 'i'
			|| str[len - 1] == 'd' || str[len - 1] == 'u'))
		cur[i++] = '+';
	if (find_in_set('-', str) != 0)
		cur[i++] = '-';
	if (find_zero_context(str) && find_in_set('-', str) == 0
		&& (str[len - 1] == 'i' || str[len - 1] == 'd' || str[len - 1] == 'u'
			|| str[len - 1] == 'x' || str[len - 1] == 'X'))
		cur[i++] = '0';
}

static void	validate_rest(const char *str, int *i, size_t len)
{
	int	skip;

	skip = *i;
	while (str[skip] && !ft_isdigit(str[skip]) && str[skip] != '.'
		&& !find_in_set(str[skip], "cspdiuxX"))
		skip++;
	while (ft_isdigit(str[skip]))
	{
		skip++;
		(*i)++;
	}
	if (str[skip] == '.' && str[len - 1] != 'c' && str[len - 1] != 'p')
	{
		(*i)++;
		skip++;
		while (ft_isdigit(str[skip]))
		{
			skip++;
			(*i)++;
		}
	}
}

char	*validate_flag(char *str, size_t length)
{
	int		i;
	int		j;
	size_t	len;
	char	currently_found[5];
	char	*new_flag;

	i = 0;
	ft_bzero(currently_found, 5);
	find_modi(str, length, currently_found);
	while (currently_found[i])
		i++;
	validate_rest(str, &i, length);
	new_flag = (char *)malloc((i + 1) * sizeof(char));
	if (!new_flag)
		return (NULL);
	j = -1;
	while (currently_found[++j])
		new_flag[j] = currently_found[j];
	len = ft_strlen(str);
	while (str[len - --i])
		new_flag[j++] = str[len - i];
	new_flag[j] = 0;
	free(str);
	return (new_flag);
}
