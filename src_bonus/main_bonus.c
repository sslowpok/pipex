/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:31:51 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/19 16:00:17 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"
#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		inp_error();
	pipex(argv, envp);
	return (0);
}
