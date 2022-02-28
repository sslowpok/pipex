/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:02 by alex              #+#    #+#             */
/*   Updated: 2022/02/28 18:53:08 by sslowpok         ###   ########.fr       */
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
** ./pipex file1 cmd1 | cmd2 > file2
** ./pipex infile "ls -l" | "wc -l" outfile
*/

void	init_fd(t_child *child)
{
	child->fd[0][0] = -1;
	child->fd[0][1] = -1;
	child->fd[1][0] = -1;
	child->fd[1][1] = -1;
	child->current_pipe = 0;
	child->i = 2;
}

// void	open_file(char *file, int flag)
// {
// 	int	fd;
	
// 	if (flag == 0) // input = 0
// 	{
// 		fd = open(file, O_RDONLY, 0777);
// 		if (fd < 0)
// 			inp_error(); // нужна функция для ошибок
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	else if (flag == 1) // output = 1
// 	{
// 		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
// 		if (fd < 0)
// 			inp_error(); // аналогично нужна функция
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// }

// void	exec_command(int argc, char **argv, const char **env, t_child *child)
// {
// 		dup2(child->fd[0], STDIN_FILENO);
// }

int	main(int argc, char **argv, const char **envp)
{
	t_child	child;

	// if (argc < 5)
	// 	inp_error();
	// init_fd(&child);
	// while (child.i < argc - 1)
	// {
	// 	// .....
	// 	child.pid = fork();
	// 	// if (child.pid == -1)
	// 	// error
	// 	// if (child.pid == 0)
	// 	//
	// 	exec_command(argc, argv, envp, &child);
	// }

	child.pid = fork();
	if (child.pid == -1)
		inp_error();
	else
		waitpid(-1, 0, 0);
	if (child.pid == 0)
		exec_command(argc, argv, envp, &child);
	return (0);
}
