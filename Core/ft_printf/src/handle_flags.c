/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:14:15 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/10 00:19:48 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	print_before(char *flag, size_t len)
{
	if (find_in_set('#', flag))
	{
		if (flag[len - 1] == 'x')
		{
			write(1, "0x", 2);
			return (-2);
		}
		else
		{
			write(1, "0X", 2);
			return (-2);
		}
	}
	return (0);
}

static int	get_len(uintptr_t nbr, int nbr2, int div, char *flag)
{
	int	i;
	int	found;

	i = 0;
	found = (find_in_set('p', flag) == 0);
	if (found && nbr2 >= 0)
	{
		if (find_in_set('+', flag) && ++i)
			write(1, "+", 1);
		else if (find_in_set(' ', flag) && ++i)
			write(1, " ", 1);
	}
	else if (nbr2 < 0)
		i++;
	if (nbr2 != 0)
		while (nbr2 && i++ >= 0)
			nbr2 /= div;
	else if (nbr != 0)
		while (nbr && i++ >= 0)
			nbr /= div;
	else
		i += (find_in_set('p', flag) != 0) * 3 + found;
	return (i);
}

static size_t	get_width_spe(char *flag, size_t len, va_list *arg_ls)
{
	ssize_t	width;
	size_t	strlen;
	int		start;
	int		end;

	start = get_modi(flag, -1);
	end = start;
	width = 0;
	while (ft_isdigit(flag[end++]))
		width = (width * 10) + flag[end - 1] - 48;
	if (flag[len - 1] == 'd' || flag[len - 1] == 'i')
		return (width - get_len(0, va_arg(*arg_ls, int), 10, flag));
	else if (flag[len - 1] == 'x' || flag[len - 1] == 'X')
		return (width - get_len(va_arg(*arg_ls, unsigned int), 0, 16, flag));
	else if (flag[len - 1] == 'c')
		return (width - (va_arg(*arg_ls, int) * 0 + 1));
	else if (flag[len - 1] == 's')
	{
		strlen = ft_strlen(va_arg(*arg_ls, char *));
		return (width - (strlen == 0) * 6 - strlen * (strlen > 0));
	}
	else if (flag[len - 1] == 'p')
		return (width - get_len(va_arg(*arg_ls, uintptr_t), 0, 16, flag) - 2);
	else
		return (width - get_len(va_arg(*arg_ls, unsigned int), 0, 10, flag));
}

static int	format_output(char *flag, va_list *arg_ls, int i)
{
	ssize_t	width;
	size_t	len;
	char	type;
	int		tmp;

	type = ' ';
	len = ft_strlen(flag);
	width = get_width_spe(flag, len, arg_ls);
	if (i && find_zero_context(flag, 1))
		type = '0';
	if (i == 0)
		if (find_in_set('#', flag))
			width -= 2;
	if (i && type == '0')
		width += print_before(flag, len);
	if (width <= 0)
		tmp = 0;
	else
		tmp = width;
	while (width-- > 0)
		write(1, &type, 1);
	if (i && type != '0')
		print_before(flag, len);
	return (tmp);
}

void	handle_flag(char *flag, va_list *arg_ls, va_list *arg_ls2, int *c)
{
	size_t	len;

	len = ft_strlen(flag);
	if (!find_in_set('-', flag))
		*c += format_output(flag, arg_ls2, 1);
	else
		if (!find_zero_context(flag, 1))
			*c += print_before(flag, len);
	if (flag[len - 1] == 'd' || flag[len - 1] == 'i')
		*c += ft_putnbr_fd(va_arg(*arg_ls, int), 1);
	else if (flag[len - 1] == 'x')
		*c += ft_putnbr_base(va_arg(*arg_ls, unsigned int), "0123456789abcdef");
	else if (flag[len - 1] == 'X')
		*c += ft_putnbr_base(va_arg(*arg_ls, unsigned int), "0123456789ABCDEF");
	else if (flag[len - 1] == 'c')
		*c += ft_putchar_fd(va_arg(*arg_ls, int), 1);
	else if (flag[len - 1] == 's')
		*c += ft_putstr_fd(va_arg(*arg_ls, char *), 1);
	else if (flag[len - 1] == 'p')
		*c += ft_putptr((uintptr_t)va_arg(*arg_ls, void *));
	else if (flag[len - 1] == 'u')
		*c += ft_putunbr_fd(va_arg(*arg_ls, unsigned int), 1);
	if (find_in_set('-', flag))
		*c += format_output(flag, arg_ls2, 0);
}
