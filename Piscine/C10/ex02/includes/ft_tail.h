/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:35:33 by kkonarze          #+#    #+#             */
/*   Updated: 2024/09/13 00:35:36 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAIL_H
# define FT_TAIL_H

# include "sys/stat.h"
# include "sys/types.h"
# include <fcntl.h>
# include "unistd.h"
# include "stdio.h"
# include "errno.h"
# include <string.h>
# include "stdlib.h"

int	ft_strlen(char *str);
int	ft_atoi(char *str);
int	ft_strcmp(char *sa, char *sb);

#endif
