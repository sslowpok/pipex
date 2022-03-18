/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:15:52 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/18 19:42:36 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/error.h"

/*
** ./pipex file1 cmd1 cmd2 file2
** ./pipex infile "ls -l" "wc -l" outfile
*/

char	**get_paths(char **envp)
{
	char	**paths;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			// paths = NULL;
			paths = paths_fill(ft_split(*envp + 5, ':'));
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
	if (!cmd)
		error(errno, "malloc: ");
	if (!access(cmd, F_OK))
		return (cmd);
	else
	{
		free(cmd);
		while (paths[i])
		{
			cmd = ft_strjoin(paths[i], cmd_flags[0]);
			if (!access(cmd, F_OK))
				break ;
			free(cmd);
			i++;
		}
	}
	return (cmd);
}

/*
 ** execve(<exact path like "usr/bin/ls">, cmd_flags, envp)
*/

void	execute_cmd(t_child *child, char *arg, char **envp)
{
	char	**paths;
	char	**cmd_flags;

	paths = get_paths(envp);
	if (!paths)
		error(errno, "malloc: ");
	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		error(errno, "malloc: ");
	child->path = make_cmd(paths, cmd_flags);
	if (execve(child->path, cmd_flags, envp) == -1)
		error(-1, cmd_flags[0]);
	free(child->path);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		inp_error();
	pipex(argv, envp);
	return (0);
}
