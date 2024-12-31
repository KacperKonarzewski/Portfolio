/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:15:25 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/11 13:44:08 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>

ssize_t	print_precision(ssize_t prec, ssize_t len);
size_t	get_precision(char *flag, size_t len, int nbr);
size_t	get_width(char *flag);
ssize_t	calculate_width(ssize_t width, ssize_t precision, ssize_t len,
			ssize_t d);
char	*validate_flag(char *str, size_t length);
int		handle_str(char *s, char *flag, int chrs);
int		handle_unsigned(unsigned int d, char *flag, int chrs);
int		handle_ptr(uintptr_t d, char *flag, int chrs);
int		handle_hex(unsigned int d, char *flag, int chrs, int capital);
int		handle_decimal(int d, char *flag, int chrs);
int		find_zero(const char *str, int con);
int		ft_printf(const char *, ...);
int		find_in_set(char c, const char *charset);
int		get_flag_length(const char *str, int per_index);
int		get_modi(const char *str, int per_i);
int		ft_putunbr_fd(unsigned int n, int fd);
int		ft_putnbr_base(unsigned int nbr, char *base);
int		ft_putptr(uintptr_t nbr);
int		get_len(uintptr_t nbr, int nbr2, int div);
int		print_width(ssize_t width, int type);

#endif
