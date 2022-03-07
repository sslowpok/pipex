/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:02 by alex              #+#    #+#             */
/*   Updated: 2022/03/02 17:19:47 by alex             ###   ########.fr       */
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

void	pipex(int f1, int f2)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	t_child	child;

	
	return (0);
}