/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:56:42 by pamartin          #+#    #+#             */
/*   Updated: 2022/03/28 14:56:44 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**path_list(char **envp)
{
	char	*path;
	char	**full_path;
	size_t	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	path = envp[i] + 5;
	full_path = ft_split(path, ':');
	return (full_path);
}

static char	*get_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

static void	execute(char **envp, char *cmd)
{
	char	**paths;
	char	**cmd_arg;
	char	*path;
	int		check;

	cmd_arg = ft_split(cmd, ' ');
	if (!cmd_arg)
		msg_error();
	paths = path_list(envp);
	if (!paths)
		msg_error();
	path = get_path(paths, cmd_arg[0]);
	if (!path)
		msg_error();
	check = execve(path, cmd_arg, envp);
	if (check == -1)
	{
		free_split(cmd_arg);
		msg_error();
	}
}

void	pipe_exec(char **envp, char *cmd, int fd_file1, int fd_file2)
{
	pid_t	child;
	int		pipe_fd[2];
	int		check;

	if (fd_file2 != 1)
	{
		check = dup2(pipe_fd[0], 0);
		protect(check);
		close_fd(pipe_fd[1], fd_file2);
		execute(envp, cmd);
	}
	check = pipe(pipe_fd);
	protect(check);
	child = fork();
	if (child == 0)
	{
		if (fd_file1 != 0)
		{
			check = dup2(pipe_fd[1], 1);
			protect(check);
			close_fd(pipe_fd[0], fd_file1);
			execute(envp, cmd);
		}
	}
	waitpid(-1, NULL, 0);
}
