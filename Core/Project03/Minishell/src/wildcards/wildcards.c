/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:09:17 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/13 12:03:13 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wildcard_match(const char *pattern, const char *filename)
{
	while (*pattern && *filename)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return (1);
			while (*filename)
				if (wildcard_match(pattern, filename++))
					return (1);
			return (0);
		}
		else if (*pattern == *filename)
		{
			pattern++;
			filename++;
		}
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern && !*filename);
}

static int	ft_init_dir_and_result(DIR **dir, char **res)
{
	*dir = opendir(".");
	if (!(*dir))
	{
		perror("opendir");
		return (0);
	}
	*res = malloc(1);
	if (!(*res))
	{
		closedir(*dir);
		*dir = NULL;
		return (0);
	}
	(*res)[0] = '\0';
	return (1);
}

static char	*ft_append_entry(char *result, size_t *len, char *entry_name)
{
	char	*new_result;
	size_t	name_len;
	size_t	new_size;

	name_len = ft_strlen(entry_name);
	new_size = (*len) + name_len + 2;
	new_result = malloc(new_size);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	if (*len > 0 && result)
		ft_strcpy(new_result, result);
	else
		new_result[0] = '\0';
	if (*len > 0)
		ft_strcat(new_result, " ");
	ft_strcat(new_result, entry_name);
	*len += (name_len + 1);
	free(result);
	return (new_result);
}

static int	ft_scan_dir(DIR *dir, char *pattern, char **result, size_t *len)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if ((ft_strcmp(entry->d_name, ".") == 0) || (ft_strcmp(entry->d_name, \
		"..") == 0))
		{
			entry = readdir(dir);
			continue ;
		}
		if (wildcard_match(pattern, entry->d_name))
		{
			*result = ft_append_entry(*result, len, entry->d_name);
			if (!(*result))
				return (0);
		}
		entry = readdir(dir);
	}
	return (1);
}

char	*expand_wildcards(char *pattern)
{
	DIR		*dir;
	char	*result;
	size_t	result_len;

	result_len = 0;
	result = NULL;
	if (!ft_init_dir_and_result(&dir, &result))
		return (ft_strdup(pattern));
	if (!ft_scan_dir(dir, pattern, &result, &result_len))
	{
		closedir(dir);
		return (ft_strdup(pattern));
	}
	closedir(dir);
	if (result_len == 0)
	{
		free(result);
		return (ft_strdup(pattern));
	}
	return (result);
}
