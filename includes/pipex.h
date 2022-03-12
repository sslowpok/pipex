/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:21 by alex              #+#    #+#             */
/*   Updated: 2022/03/12 17:01:12 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../printf/ft_printf.h"

# define INPUT	0
# define OUTPUT	1

typedef struct s_child
{
	char	*path;
	char	*cmd_path;
	char	**envp;
	pid_t	child1;
	pid_t	child2;
	int		fd[2];
	// int		current_pipe;
	// int		i;
}			t_child;

void	ft_putendl_fd(char *s, int fd);
char	**ft_split(const char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_sstrlen(const char *str);

#endif