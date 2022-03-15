/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:15:52 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/15 17:30:37 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/error.h"

void	inp_error(void)
{
	ft_putendl_fd("Invalid input.", 2);
	exit(1);
}

/*
** ./pipex file1 cmd1 cmd2 file2
** ./pipex infile "ls -l" "wc -l" outfile
*/

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

char	**get_paths(char **envp) // returns **char of all paths from "PATH="
{
	char	**paths;
	char	*tmp;
	int	i;

	i = 0;
	
	while (*envp) // *envp or envp?
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			paths = ft_split(*envp + 5, ':');
			if (!paths)
				error(errno, "malloc: ");
			while (paths[i])
			{
				tmp = ft_strjoin(paths[i], "/");
				if (!tmp)
					error(errno, "malloc: ");
				free(paths[i]);
				paths[i] = ft_strdup(tmp);
				if (!paths[i])
					error(errno, "malloc: ");
				free(tmp);
				i++;
			}
			return (paths);
		}
		envp++;
	}
	return (0);
}

char	*make_cmd(char **paths, char **cmd_flags)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	cmd = ft_strdup(cmd_flags[0]);
	if (!cmd)
		error(errno, "malloc: ");
	if (!access(cmd,F_OK))
		return (cmd);
	else
	{
		free(cmd);
		while (paths[i])
		{
			cmd = ft_strjoin(paths[i], cmd_flags[0]);
			if (!access(cmd, F_OK))
				break;
			free(cmd);
			i++;
		}
	}
	return (cmd);
}

void	execute_cmd(t_child *child, char *arg, char **envp) // arg = command (argv[2] or argv[3])
{
	char	**paths;
	char	**cmd_flags;

	paths = get_paths(envp);

	if (!paths)
		error(errno, "malloc: ");
	// while (*paths)
	// {
	// 	ft_printf("%s\n", *paths);
	// 	paths++;
	// }
	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		error(errno, "malloc: ");
	child->path = make_cmd(paths, cmd_flags);
	if (execve(child->path, cmd_flags, envp) == -1)
		error(-1, cmd_flags[0]);
	free(child->path);
	// execve(<exact path like "usr/bin/ls">, cmd_flags, envp)
}

void	child_one(t_child *child, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0644);
	if (fd_in < 0)
		error(errno, argv[1]);
	
	if (dup2(fd_in, STDIN_FILENO) < 0) // makes stdin = fd_in from file
		error(errno, "Error: ");
	if (dup2(child->fd[1], STDOUT_FILENO) < 0) // make stdout = fd_out to fd[1]
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

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		inp_error();

	pipex(argv, envp);
	return (0);
}
