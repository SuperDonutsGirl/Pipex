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

void	create_heredoc(char **argv)
{
	char	*line;
	int		here_doc;

	here_doc = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	protect(here_doc);
	line = get_next_line(0);
	while (line && (ft_strncmp(line, argv[2], ft_strlen(argv[2]))
			|| ft_strlen(argv[2]) + 1 != ft_strlen(line)))
	{
		write(here_doc, line, ft_strlen(line));
		line = get_next_line(0);
	}
	free(line);
}

int	open_files(int argc, char **argv, int *fd_file, int type)
{
	if (!ft_strncmp(argv[1], "here_doc", 9) && (argc == 6))
	{
		create_heredoc(argv);
		fd_file[0] = open(argv[1], O_RDONLY);
		fd_file[1] = open(argv[argc - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
		type = 1;
	}
	else if (!ft_strncmp(argv[1], "here_doc", 9) && (argc != 6))
	{
		ft_putstr_fd("Error : with here_doc it takes 5 arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		fd_file[0] = open(argv[1], O_RDONLY);
		fd_file[1] = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
		type = 0;
	}
	if (fd_file[0] < 0 || fd_file[1] < 0)
		msg_error();
	return (type);
}

int	main(int argc, char**argv, char **envp)
{
	int	fd_file[2];
	int	check;
	int	type;
	int	i;

	if (argc < 5)
		return (ft_putstr_fd("Error : you need at least 4 arguments\n", 2));
	check = open_files(argc, argv, fd_file, type);
	if (check)
	{
		argc--;
		argv++;
	}
	pipe_exec(argc, argv, envp, fd_file);
	if (check)
		unlink("here_doc");
	return (0);
}
