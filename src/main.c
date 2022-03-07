/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:02 by alex              #+#    #+#             */
/*   Updated: 2022/03/07 11:35:54 by sslowpok         ###   ########.fr       */
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

void	child_one(int )

void	pipex(char **argv, char **envp)
{
	t_child	child;

	if (pipe(child.fd) == -1)
		exit(1);
	// child.fd[0] = open(O_RDONLY, 0777);
	child.child1 = fork();
	if (child.child1 < 0)
		exit(1);
	else if (child.child1 == 0)
	
}

int	main(int argc, char **argv, char **envp)
{
	// if (argc < 5)
	// 	inp_error();
	pipex(argv, envp);
	return (0);
}