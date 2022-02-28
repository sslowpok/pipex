/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:21 by alex              #+#    #+#             */
/*   Updated: 2022/02/28 18:51:39 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../printf/ft_printf.h"

typedef struct s_child
{
	char	*path;
	char	**envp;
	pid_t	pid;
	int		fd[2];
	int		current_pipe;
	int		i;
}			t_child;

void	ft_putendl_fd(char *s, int fd);

#endif