/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:15:52 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/15 16:16:05 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/error.h"

void	inp_error(void)
{
	ft_putendl_fd("Invalid input.", 2);
	exit(INVALID_DATA);
}

/*
** ./pipex file1 cmd1 cmd2 file2
** ./pipex infile "ls -l" "wc -l" outfile
*/

void	make_children(t_child *child)
{
	if (!child)
		exit(1);
	child->path = NULL;
	child->cmd_path = NULL;
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
				exit(1);
			while (paths[i])
			{
				tmp = ft_strjoin(paths[i], "/");
				if (!tmp)
					exit(1);
				free(paths[i]);
				paths[i] = ft_strdup(tmp);
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
	if (!cmd)
		exit (1);
	return (cmd);
}

void	execute_cmd(t_child *child, char *arg, char **envp) // arg = command (argv[2] or argv[3])
{
	char	**paths;
	char	**cmd_flags;

	paths = get_paths(envp);

	if (!paths)
		exit(1);
	// while (*paths)
	// {
	// 	ft_printf("%s\n", *paths);
	// 	paths++;
	// }
	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		exit(1);
	child->path = make_cmd(paths, cmd_flags);
	if (execve(child->path, cmd_flags, envp) == -1)
		exit (1);
	free(child->path);
	//free(child->cmd_path);
	// execve(<exact path like "usr/bin/ls">, cmd_flags, envp)
}

void	child_one(t_child *child, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		exit(1);
	
	if (dup2(fd_in, STDIN_FILENO) < 0) // makes stdin = fd_in from file
		exit(1);
	if (dup2(child->fd[1], STDOUT_FILENO) < 0) // make stdout = fd_out to fd[1]
		exit(1);
	
	close(fd_in);
	close(child->fd[0]);
	close(child->fd[1]);
	
	execute_cmd(child, argv[2], envp);
}

void	child_two(t_child *child, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (fd_out < 0)
		exit (1);
	if (dup2(child->fd[0], STDIN_FILENO) < 0)
		exit (1);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		exit (1);
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
		exit(1);
	child.child1 = fork();
	if (child.child1 < 0)
		exit(1);
	else if (child.child1 == 0)
		child_one(&child, argv, envp);
	child.child2 = fork();
	if (child.child2 < 0)
		exit(1);
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
