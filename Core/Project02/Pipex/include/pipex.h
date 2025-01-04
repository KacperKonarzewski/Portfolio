/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:49:52 by kkonarze          #+#    #+#             */
/*   Updated: 2025/01/04 22:30:19 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

void	error(int i, char *str);
void	use_cmd(char *cmd, char **envp);
int		get_input(char **line);
int		file_opener(char *argv, int i);

#endif
