/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:56:56 by pamartin          #+#    #+#             */
/*   Updated: 2022/03/28 14:56:58 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

//Utils
int		ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
void	*free_split(char **split);

//Error Protection and Close
void	msg_error(void);
void	protect(int check);
void	close_fd(int pipe_fd, int file_fd);

//pipe
void	pipe_exec(char **envp, char *cmd, int fd_file1, int fd_file2);

#endif
