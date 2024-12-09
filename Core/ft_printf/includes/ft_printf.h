/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:15:25 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/10 00:20:23 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>

char	*validate_flag(char *str, size_t length);
int		find_zero_context(const char *str, int con);
int		ft_printf(const char *str, ...);
int		find_in_set(char c, const char *charset);
int		get_flag_length(const char *str, int per_index);
int		get_modi(const char *str, int per_i);
int		ft_putunbr_fd(unsigned int n, int fd);
int		ft_putnbr_base(unsigned int nbr, char *base);
int		ft_putptr(uintptr_t nbr);
void	handle_flag(char *flag, va_list *arg_ls, va_list *arg_ls2, int *c);

#endif
