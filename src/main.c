/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:02 by alex              #+#    #+#             */
/*   Updated: 2022/02/23 15:11:39 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/error.h"

void	inp_error(void)
{
	ft_putendl_fd("Invalid input.", 2);
	exit (INVALID_DATA);
}

/*
** ./pipex file1 cmd1 | cmd2 > file2
** ./pipex infile "ls -l" "wc -l" outfile
*/

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		inp_error();
	pipex(argv, envp);
	return (0);
}
