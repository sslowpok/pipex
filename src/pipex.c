/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:21:45 by sslowpok          #+#    #+#             */
/*   Updated: 2022/02/22 18:00:48 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int f1, t_cmd cmd1)
{
	
}

void	pipex(int f1, int f2, char **argv, char **envp)
{
	// cmd[1] is child process, cmd[0] is parent process
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	// if (!parent) // if fork returns 0, we are in the child process
	// 	child_process(f2, cmd2);
	// else
	// 	parent_process(f2, cmd2);
}