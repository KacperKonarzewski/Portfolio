/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:09:17 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/12 20:03:42 by kkonarze         ###   ########.fr       */
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
	return (*pattern == '\0' && *filename == '\0');
}

char *expand_wildcards(char *pattern)
{
    DIR *dir;
    struct dirent *entry;
    char *result = NULL;
    size_t result_len = 0;

    dir = opendir(".");
    if (!dir)
    {
        perror("opendir");
        return ft_strdup(pattern);
    }

    result = malloc(1);
    if (!result)
    {
        closedir(dir);
        return ft_strdup(pattern);
    }
    result[0] = '\0';

    while ((entry = readdir(dir)) != NULL)
    {
        if (wildcard_match(pattern, entry->d_name))
        {
            size_t name_len = strlen(entry->d_name);
            char *new_result = realloc(result, result_len + name_len + 2);
            if (!new_result)
            {
                free(result);
                closedir(dir);
                return ft_strdup(pattern);
            }
            result = new_result;
            if (result_len > 0)
                strcat(result, " ");
            strcat(result, entry->d_name);
            result_len += name_len + 1;
        }
    }
    closedir(dir);

    if (result_len == 0)
    {
        free(result);
        return ft_strdup(pattern);
    }
    return result;
}

