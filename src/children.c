/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:14:51 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/16 17:39:07 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/error.h"

void	make_children(t_child *child)
{
	if (!child)
		error(errno, "malloc: ");
	child->path = NULL;
	child->child1 = 0;
	child->child2 = 0;
	child->fd[0] = -1;
	child->fd[1] = -1;
}

void	child_one(t_child *child, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0644);
	if (fd_in < 0)
		error(errno, argv[1]);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		error(errno, "Error: ");
	if (dup2(child->fd[1], STDOUT_FILENO) < 0)
		error(errno, "Error: ");
	close(fd_in);
	close(child->fd[0]);
	close(child->fd[1]);
	execute_cmd(child, argv[2], envp);
}

void	child_two(t_child *child, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error(errno, argv[4]);
	if (dup2(child->fd[0], STDIN_FILENO) < 0)
		error(errno, "Error: ");
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		error(errno, "Error: ");
	close(fd_out);
	close(child->fd[0]);
	close(child->fd[1]);
	execute_cmd(child, argv[3], envp);
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
	child.child2 = fork();
	if (child.child2 < 0)
		error(errno, "fork: ");
	else if (child.child2 == 0)
		child_two(&child, argv, envp);
	close(child.fd[0]);
	close(child.fd[1]);
	waitpid(child.child1, NULL, 0);
	waitpid(child.child2, NULL, 0);
}

char	**paths_fill(char **paths)
{
	int		i;
	char	*tmp;

	if (!paths)
		error(errno, "malloc: ");
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			error(errno, "malloc: ");
		free(paths[i]);
		paths[i] = ft_strdup(tmp);
		if (!paths[i] || !tmp)
			error(errno, "malloc: ");
		free(tmp);
		i++;
	}
	return (paths);
}