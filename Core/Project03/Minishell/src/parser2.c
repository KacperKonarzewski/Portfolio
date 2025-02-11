/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:29:31 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/11 12:31:50 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redo_str(char **split, char *key, ptrdiff_t chars[2], int *status)
{
	char	*new_str;
	int		i;

	i = -1;
	if (!ft_strcmp(key, "$?"))
		handle_status(split, key, chars, status);
	else
	{
		new_str = (char *)malloc(chars[0] + chars[1] + 1);
		if (!new_str)
			return ;
		while (++i < (int)chars[0])
			new_str[i] = (*split)[i];
		i = -1;
		while (++i < (int)chars[1])
			new_str[i + chars[0]] = (*split)[chars[0] + ft_strlen(key) + i];
		new_str[chars[0] + chars[1]] = 0;
		free(*split);
		*split = new_str;
	}
}

int	find_key(char **split, char *key, int *status, t_env_var *envp)
{
	char		*env;
	char		*new_str;
	int			i;
	ptrdiff_t	chars[2];
	size_t		len;

	(void)status;
	chars[0] = ft_strnstr(*split, key, ft_strlen(*split)) - *split;
	chars[1] = (ptrdiff_t)(ft_strlen(*split) - ft_strlen(key)) - chars[0];
	env = get_env_var(envp, key + 1);
	if (!env)
		return (redo_str(split, key, chars, status), free(key), 1);
	i = -1;
	len = ft_strlen(env);
	new_str = (char *)malloc(chars[0] + len + chars[1] + 1);
	while (++i < (int)chars[0])
		new_str[i] = (*split)[i];
	while (i++ - (int)chars[0] < (int)len)
		new_str[i - 1] = env[i - 1 - (int)chars[0]];
	i = -1;
	while (++i < (int)chars[1])
		new_str[i + (int)len + (int)chars[0]] = (*split)[i + ft_strlen(key) \
		+ chars[0]];
	new_str[i + (int)len + (int)chars[0]] = 0;
	return (free(env), free(key), free(*split), *split = new_str, 1);
}

char	*extract_key(char *splitted)
{
	char	*key;
	int		start;
	int		end;
	int		i;

	start = 0;
	while (splitted[start] && splitted[start] != '$')
		start++;
	end = start + 1;
	while (!ft_isdigit(splitted[start + 1]) && \
		(ft_isalnum(splitted[end]) || splitted[end] == '_'))
		end++;
	end += (end == start + 1);
	key = malloc(sizeof(char) * (end - start + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (start + i++ < end)
		key[i - 1] = splitted[start + i - 1];
	key[end - start] = 0;
	return (key);
}

void	handle_space(char **text, int type)
{
	size_t	len;

	len = ft_strlen(*text);
	if (text[1] == 0)
		return ;
	if ((*text)[len - 1] != ' ' || type)
		(*text)[len - 1] = 0;
}

void	remove_quotes(char **text, int type)
{
	int		space[2];
	char	*joined[2];

	space[0] = 0;
	space[1] = 0;
	if ((*text)[ft_strlen((*text)) - 1] == ' ')
	{
		space[0] = 1;
		(*text)[ft_strlen(*text) - 1] = 0;
	}
	if ((*text)[0] == '\"' && ++(space[1]))
		joined[0] = ft_strtrim((*text), "\"");
	else if ((*text)[0] == '\'' && ++(space[1]))
		joined[0] = ft_strtrim((*text), "\'");
	if (space[1])
	{
		free((*text));
		(*text) = joined[0];
	}
	if (!type && space[0])
	{
		joined[1] = ft_strjoin((*text), " ");
		free((*text));
		(*text) = joined[1];
	}
}
