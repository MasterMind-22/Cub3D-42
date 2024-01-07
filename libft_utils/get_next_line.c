/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:26:05 by yonadry           #+#    #+#             */
/*   Updated: 2024/01/07 18:26:10 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*read_fd(int fd, char *read_line)
{
	int		read_int;
	char	*from_read;

	read_int = 1;
	from_read = malloc(BUFFER_SIZE + 1);
	if (!from_read)
		return (NULL);
	while (newline_found(read_line) && read_int)
	{
		read_int = read(fd, from_read, BUFFER_SIZE);
		if (read_int == -1 || (read_int == 0 && !read_line))
			return (free(from_read), free(read_line), NULL);
		from_read[read_int] = '\0';
		read_line = ft_strjoin(read_line, from_read);
	}
	free(from_read);
	if (read_line[0] == '\0')
	{
		free(read_line);
		return (NULL);
	}
	return (read_line);
}

char	*return_line_f(char *read_line)
{
	int		i;
	char	*return_line;

	i = -1;
	while (read_line[++i])
	{
		if (read_line[i] == '\n')
		{
			i++;
			break ;
		}
	}
	return_line = (char *)malloc((i + 1) * sizeof(char));
	if (!return_line)
		return (NULL);
	i = -1;
	while (read_line[++i] && read_line[i] != '\n')
		return_line[i] = read_line[i];
	if (read_line[i] == '\n')
	{
		return_line[i] = '\n';
		i++;
	}
	return_line[i] = '\0';
	return (return_line);
}

char	*save_line_f(char *read_line)
{
	int		i;
	char	*save_line;
	int		j;

	j = 0;
	i = -1;
	while (read_line[++i])
	{
		if (read_line[i] == '\n')
		{
			i++;
			break ;
		}
	}
	save_line = malloc(ft_strlen(&read_line[i]) + 1);
	if (!save_line)
		return (free(read_line), NULL);
	while (read_line[i])
	{
		save_line[j] = read_line[i];
		i++;
		j++;
	}
	save_line[j] = '\0';
	return (free(read_line), save_line);
}

char	*get_next_line(int fd)
{
	char		*return_line;
	static char	*read_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line = read_fd(fd, read_line);
	if (!read_line)
		return (NULL);
	return_line = return_line_f(read_line);
	read_line = save_line_f(read_line);
	return (return_line);
}
