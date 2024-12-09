/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:56:00 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/09 22:08:28 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static char	*get_flag(const char *str, int *i)
{
	char	*flag;
	size_t	len;
	int		total_length;

	total_length = get_flag_length(str, *i);
	if (total_length == -1)
		return (NULL);
	flag = ft_substr(str, (*i) + 1, total_length);
	if (flag == NULL)
		return (NULL);
	len = ft_strlen(flag);
	*i += len;
	flag = validate_flag(flag, len);
	if (flag == NULL)
		return (NULL);
	return (flag);
}

static int	write_flags(const char *str, va_list *arg_ls, va_list *arg_ls2)
{
	int		i;
	int		chars;
	char	*flag;

	while (str[i])
	{
		flag = NULL;
		if (str[i] == '%' && str[i + 1] != '%')
		{
			flag = get_flag(str, &i);
			if (flag == NULL)
				return (0);
			handle_flag(flag, arg_ls, arg_ls2, &chars);
			free(flag);
		}
		else
		{
			write(1, &str[i], 1);
			chars++;
		}
		i = i + 1 + (str[i] == '%' && str[i + 1] == '%');
	}
	return (chars);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg_ls;
	va_list	arg_ls2;
	int		chars;

	chars = 0;
	va_start(arg_ls, str);
	va_copy(arg_ls2, arg_ls);
	chars = write_flags(str, &arg_ls, &arg_ls2);
	va_end(arg_ls2);
	va_end(arg_ls);
	return (chars);
}
