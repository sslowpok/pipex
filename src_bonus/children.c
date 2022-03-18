/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:07:14 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/18 19:52:45 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/error.h"

void	make_children(t_child *child)
{
	if (!child)
		error(errno, "");
	child->path = NULL;
	child->child1 = 0;
	child->child2 = 0;
	child->fd[0] = -1;
	child->fd[1] = -1;
}

char	*make_cmd(char **paths, char **cmd_flags)
{
	char	*cmd;
	int		i;

	i = 0;
	// cmd = NULL;		needed???
	// cmd = ft_strdup(cmd 
	// 	IM HERE
}

void	execute_cmd(t_child *child, char *arg, char **envp)
{
	char	**paths;
	char	**cmd_flags;

	paths = get_paths(envp);
	if (!paths)
		error(errno, "malloc: ");
	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		error(errno, "malloc: ");
	child->path = make_cmd(paths, cmd_flags);
	// im here
}

void	child_one(t_child *child, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0644);
	if (fd_in < 0)
		error(errno, "Error: ");
	if (dup2(fd_in, STDIN_FILENO) < 0)
		error(errno, "Error: ");
	if (dup2(child->fd[1], STDOUT_FILENO) < 0)
		error(errno, "Error: ");
	close(fd_in);
	close(child->fd[0]);
	close(child->fd[1]);
	execute_cmd(child, argv[2], envp);
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
