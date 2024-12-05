/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:15:25 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/05 13:53:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>

char	*validate_flag(char *str, size_t length);
int		ft_printf(const char *str, ...);
int		find_in_set(char c, const char *charset);
int		get_flag_length(const char *str, int per_index);

#endif
