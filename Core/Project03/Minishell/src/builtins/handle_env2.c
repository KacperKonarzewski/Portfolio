/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 07:32:59 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/05 07:49:17 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env_var(t_env_var **head, const char *key)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static char	*create_entry(const char *key, const char *value)
{
	char	*entry;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	entry = ft_strjoin(tmp, value);
	free(tmp);
	return (entry);
}

char	**build_env_array(t_env_var **head)
{
	t_env_var	*current;
	int			count;
	char		**envp;
	int			i;

	current = *head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	envp = malloc((count + 1) * sizeof(char *));
	current = *head;
	i = -1;
	while (++i < count)
	{
		envp[i] = create_entry(current->key, current->value);
		current = current->next;
	}
	envp[count] = NULL;
	return (envp);
}
