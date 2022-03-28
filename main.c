/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:36:18 by pamartin          #+#    #+#             */
/*   Updated: 2022/03/28 16:36:20 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msg_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	protect(int check)
{
	if (check == -1)
		msg_error();
}

void	close_fd(int pipe_fd, int file_fd)
{
	close(pipe_fd);
	close(file_fd);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_file1;
	int		fd_file2;
	int		check;

	if (argc != 5)
		return (ft_putstr_fd("Error : bad arguments\n", 2));
	fd_file1 = open(argv[1], O_RDONLY);
	fd_file2 = open(argv[4], O_CREAT | O_RDWR, 0644);
	if (fd_file1 < 0 || fd_file2 < 0)
		msg_error();
	check = dup2(fd_file1, 0);
	protect(check);
	check = dup2(fd_file2, 1);
	protect(check);
	pipe_exec(envp, argv[2], fd_file1, 1);
	pipe_exec(envp, argv[3], 0, fd_file2);
	return (0);
}
