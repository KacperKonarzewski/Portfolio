/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:56:00 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/05 14:15:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*get_flag(const char *str, int per_index)
{
	char	*flag;
	int		total_length;

	total_length = get_flag_length(str, per_index);
	if (total_length == -1)
		return (NULL);
	flag = ft_substr(str, per_index + 1, total_length);
	return (flag);
}

static void	write_flags(const char *str, va_list arg_ls)
{
	int		i;
	size_t	len;
	char	*flag;

	i = 1;
	while (str[i])
	{
		flag = NULL;
		if (str[i] == '%')
		{
			flag = get_flag(str, i);
			if (flag == NULL)
				return ;
			len = ft_strlen(flag);
			i += len;
			flag = validate_flag(flag, len);
			if (flag == NULL)
				return ;
			printf("%s", str);
		}
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	arg_ls;

	va_start(arg_ls, str);
	write_flags(str, arg_ls);
	va_end(arg_ls);
	return (0);
}
