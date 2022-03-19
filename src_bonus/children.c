/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:37:46 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/19 18:08:52 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	make_children(t_child *child)
{
	child->child1 = 0;
	child->child2 = 0;
	child->child3 = 0;
	child->path = NULL;
	child->fd[0] = -1;
	child->fd[1] = -1;
	child->fd_in = open(argv[1], O_RDONLY, 0644);
	if (child->fd_in < 0)
		error(errno, "Error: ");
	child->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644)
}

void	child_one(t_child *child, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0644);
	if (fd_in < 0)
		error(errno, "Error: ");
	if (dup2(fd_in, STDIN_FILENO) < 0)
		error(errno, "Error: ");
	close(fd_in);
	if (dup2(child->fd[1], STDOUT_FILENO) < 0)
		error(errno, "Error: ");
	close(child->fd[1]);
	execute_cmd(child, argv[2], envp);
}

void	child_two(t_child *child, char **argv, char **envp)
{
	
}

void	pipex(char **argv, char **envp)
{
	t_child	child;

	make_children(&child);
	if (pipe(child.fd) == -1)
		error(errno, "pipex: ");
	child.child1 = fork();
	if (child.child1 < 0)
		error(errno, "fork: ");
	else if (child.child1 == 0)
		child_one(&child, argv, envp);
	waitpid(child.child1, NULL, 0);
}