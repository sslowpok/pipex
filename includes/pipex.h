/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:21 by alex              #+#    #+#             */
/*   Updated: 2022/02/23 15:11:25 by sslowpok         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	**cmd1;
	char	**cmd2;
}		t_cmd;

typedef struct s_process
{
	pid_t	child1;
	pid_t	child2;
}		t_process;


void	ft_putendl_fd(char *s, int fd);
void	pipex(char **argv, char **envp);

#endif