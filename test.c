/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:04:05 by sslowpok          #+#    #+#             */
/*   Updated: 2022/02/28 16:06:26 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		printf("Hello from child\n");
	else
		printf("Hello from parent\n");
	return (0);
}