/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:01:45 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/13 01:01:46 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEXDUMP_H
# define FT_HEXDUMP_H

# include "sys/stat.h"
# include "sys/types.h"
# include <fcntl.h>
# include "unistd.h"
# include "stdio.h"
# include "errno.h"
# include <string.h>
# include "stdlib.h"

char	*get_line(void);
int		ft_strlen(char *str);
int		ft_strncmp(char *sa, char *sb, unsigned int n);
void	print_hex(char *line, long nb);
void	ft_putnbr_hex(long nb);
int		check_fd(char *file, int i);
char	**check_and_delete(int ac, char **av, int i);

#endif
