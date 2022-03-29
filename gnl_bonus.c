/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:39:43 by pamartin          #+#    #+#             */
/*   Updated: 2022/03/29 17:39:49 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	is_line(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*read_file(char *rest, int fd)
{
	char	*reading;
	int		rc;

	reading = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!reading)
		return (NULL);
	rc = 1;
	while (rc && !ft_strchr(rest, '\n'))
	{
		rc = read(fd, reading, BUFFER_SIZE);
		if (rc < 0)
			return (ft_free(reading));
		reading[rc] = '\0';
		rest = ft_strjoin_gnl(rest, reading);
	}
	ft_free(reading);
	return (rest);
}

char	*get_line(char *rest, size_t i)
{
	char	*line;
	size_t	y;

	if (!rest[0])
		return (NULL);
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	y = 0;
	while (rest[i] && rest[i] != '\n')
		line[y++] = rest[i++];
	if (rest[i] == '\n')
		line[y++] = rest[i];
	line[y] = '\0';
	return (line);
}

char	*recover_rest(char *rest, size_t i)
{
	char	*save;
	size_t	y;

	if (!rest[0])
		return (ft_free(rest));
	save = malloc(sizeof(char) * (ft_strlen(rest) - i) + 1);
	if (!save)
		return (NULL);
	y = 0;
	while (rest[i])
		save[y++] = rest[i++];
	save[y] = '\0';
	ft_free(rest);
	return (save);
}

char	*get_next_line(int fd)
{
	char static	*rest;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	rest = read_file(rest, fd);
	if (!rest)
		return (NULL);
	line = get_line(rest, is_line(rest));
	rest = recover_rest(rest, is_line(rest));
	return (line);
}

/*
int main (void)
{
	int fd;
	char *line;

	fd = open("file", O_RDONLY);
	//fd = -2;


	line = get_next_line(fd);
	printf("ligne 1 : %s", line);
	
	 line = get_next_line(fd);
	 printf("ligne 2 : %s", line);

	 line = get_next_line(fd);
	 printf("ligne 3 : %s", line);

	 line = get_next_line(fd);
	 printf("ligne 4 : %s", line);

	 line = get_next_line(fd);
	 printf("ligne 5 : %s", line);

	 line = get_next_line(fd);
	 printf("ligne 6 : %s", line);


	//close(fd);

	line = get_next_line(fd);
	printf("ligne 7 : %s", line);
	
}*/
