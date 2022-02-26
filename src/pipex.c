/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:21:45 by sslowpok          #+#    #+#             */
/*   Updated: 2022/02/26 17:15:19 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int f1, t_cmd cmd1)
{
	
}

// void	pipex(int f1, int f2)
// {
// 	pid_t	child;
// 	pid_t	parent;
// 	int		fd[2];

// 	// if (pipe(fd) == -1)
// 	// 	warning(errno, "pipex: ");
// 	// child1 = fork();
// 	// if (child1 < 0)
// 	// 	...
// 	// if (!child1)
// 	//	 child_one(fd, argv, envp)
// 	// child2 = fork();
// 	// if (child2 < 0)
// 	// ...
// 	// if (!child2)
// 	// 	child_two(fd, argv, envp)
// 	// close(fd[0]);
// 	// close(fd[1]);
// 	// waitpid(child1, NULL, 0);
// 	// waitpid(child2, NULL, 0);
// }


// end[1] - child process
// end[0] - parent process
// cmd1 is executed by thr child, cmd2 - by the parent
void	pipex(int f1, int f2)
{
	int		end[2];
	pid_t	parent;
	pid_t	child;

	pipe(end);	// link together the processes
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	if (parent == 0) // means we are in the child process
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}