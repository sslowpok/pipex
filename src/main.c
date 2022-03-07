/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:02 by alex              #+#    #+#             */
/*   Updated: 2022/03/07 13:46:34 by sslowpok         ###   ########.fr       */
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

char	**get_paths(char **envp)
{
	char	**paths;
	char	*tmp;
	int	i;

	i = 0;
	while (*envp)
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

void	execute_cmd(t_child *child, char *arg, char **envp) // arg = command (argv[2] or argv[3])
{
	char	**paths;
	char	**cmd_flags;

	paths = get_paths(envp);
	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		exit(1);
	// child->cmd_path
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
	// execute_cmd(argv[2], envp);
}

void	child_two(t_child *child, char **argv, char **envp)
{
	return ;
}

void	pipex(char **argv, char **envp)
{
	t_child	child;

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
}

int	main(int argc, char **argv, char **envp)
{
	// if (argc < 5)
	// 	inp_error();
	pipex(argv, envp);
	return (0);
}
