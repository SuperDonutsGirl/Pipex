/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:28:37 by pamartin          #+#    #+#             */
/*   Updated: 2022/03/28 18:28:38 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	main(int argc, char**argv, char **envp)
{
	int	fd_file[2];
	int	check;
	int	i;

	if (argc < 5)
		return (ft_putstr_fd("Error : you need at least 4 arguments\n", 2));
	fd_file[0] = open(argv[1], O_RDONLY);
	fd_file[1] = open(argv[argc - 1], O_CREAT | O_RDWR, 0644);
	if (fd_file[0] < 0 || fd_file[1] < 0)
		msg_error();
	pipe_exec(argc, argv, envp, fd_file);
	return (0);
}
