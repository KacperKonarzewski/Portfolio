/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonarze <kkonarze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:51:53 by kkonarze          #+#    #+#             */
/*   Updated: 2024/12/31 17:46:11 by kkonarze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	if (argc < 2)
        return 0;
    int fd = open("command.sh", O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (fd < 0) {
        perror("error creating file");
        exit(-1);
    }
    write(fd, "#!/bin/sh\n", 10);
    write(fd, argv[1], ft_strlen(argv[1]));
    close(fd);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        char *args[] = {"/bin/sh", "command.sh", NULL};
        char *env[] = { "PATH=/bin", NULL };
        if (execve("command.sh", args, env) == -1) {
            perror("execve");
            exit(1);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        /*if (unlink("command.sh") == -1) {
            perror("unlink");
            return 1;
        }*/
    }
    return 0;
}
