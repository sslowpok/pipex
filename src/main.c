/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:02 by alex              #+#    #+#             */
/*   Updated: 2022/02/21 18:38:57 by sslowpok         ###   ########.fr       */
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

int	main(int argc, __unused char **argv, __unused char **envp)
{
	int	f1;
	int	f2;
	
	if (argc != 5)
		inp_error();
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT, O_RDWR, O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	pipex(f1, f2, argv, envp);
	return (0);
}
