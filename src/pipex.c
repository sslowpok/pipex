/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:21:45 by sslowpok          #+#    #+#             */
/*   Updated: 2022/02/23 15:58:28 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int f1, t_cmd cmd1)
{
	
}

void	pipex(char **argv, char **envp)
{
	pid_t	child1;
	pid_t	child2;
	int		fd[2];

	// if (pipe(fd) == -1)
	// 	warning(errno, "pipex: ");
	child1 = fork();
	// if (child1 < 0)
	// 	...
	// if (!child1)
	//	 child_one(fd, argv, envp)
	child2 = fork();
	// if (child2 < 0)
	// ...
	// if (!child2)
	// 	child_two(fd, argv, envp)
	close(fd[0]);
	close(fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
}