/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:44:12 by kkonarze          #+#    #+#             */
/*   Updated: 2025/02/05 00:45:59 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_var(t_env_var **head, const char *key, const char *value)
{
	t_env_var	*current;
	t_env_var	*new_var;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = *head;
	*head = new_var;
}

char	*get_env_var(t_env_var *head, const char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	envp_to_list(t_env_var **head, char **envp)
{
	t_env_var	*new_var;
	char		*entry;
	char		*equal_sign;
	int			i;

	i = -1;
	while (envp[++i])
	{
		entry = ft_strdup(envp[i]);
		equal_sign = ft_strchr(entry, '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			new_var = malloc(sizeof(t_env_var));
			if (!new_var)
				return ;
			new_var->key = ft_strdup(entry);
			new_var->value = ft_strdup(equal_sign + 1);
			new_var->next = *head;
			*head = new_var;
		}
		free(entry);
	}
}

int	print_env_vars(t_env_var *current)
{
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (1);
}

void	free_env_list(t_env_var **head)
{
	t_env_var	*current;
	t_env_var	*temp;

	current = *head;
	while (current)
	{
		temp = current;
		free(current->key);
		free(current->value);
		current = current->next;
		free(temp);
	}
	*head = NULL;
}
void unset_env_var(const char *key)
{
	EnvVar *current = env_list;
	EnvVar *prev = NULL;

	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
			{
				env_list = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			free(current->key);
			free(current->value);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}
