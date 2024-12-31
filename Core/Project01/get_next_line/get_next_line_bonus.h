/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:37:16 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/16 22:23:14 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 10

# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_linelst
{
	int					fd;
	int					current_line;
	char				*buffor;
	struct s_linelst	*next;
}			t_linelst;

t_linelst	*find_lst(t_linelst **lst, int fd);
t_linelst	*create_node(int fd);
char		*get_next_line(int fd);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);

#endif