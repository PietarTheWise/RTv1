/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:04:21 by pietari           #+#    #+#             */
/*   Updated: 2022/03/18 12:57:40 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Create substring of buffer until \n. Combine line and the substring. 
** If i is not equal to length of buffer, a \n was found. In this case
** we use ft_memcpy to copy buffer after \n to the start of the buffer 
** without a need to malloc.
** If no \n was found, bzero buffer and read into it again. This is done
** as long as we encounter a \n.
*/
size_t	ft_strclen(const char *str, int c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != (unsigned char)c)
	{
		len++;
	}
	return (len);
}

static void	ft_add_to_line(int fd, char **line, char **buffer, size_t i)
{
	char	*free1;
	char	*free2;

	free1 = ft_strsub(*buffer, 0, i);
	free2 = *line;
	*line = ft_strjoin(*line, free1);
	ft_bzero(free1, ft_strlen(free1));
	ft_bzero(free2, ft_strlen(free2));
	free(free1);
	free(free2);
	free1 = NULL;
	free2 = NULL;
	if (i != ft_strlen(*buffer))
	{
		ft_memcpy(*buffer, (*buffer) + i + 1, BUFF_SIZE - i);
		ft_bzero(*buffer + (BUFF_SIZE - i), i);
	}
	else
	{
		ft_bzero(*buffer, BUFF_SIZE);
		if (read(fd, *buffer, BUFF_SIZE))
			ft_add_to_line(fd, line, buffer, ft_strclen(*buffer, '\n'));
	}
}

/* Count the length to \n. Mallocate for line. */
static char	*ft_create_line(const int fd, char **buffer)
{
	char	*line;
	size_t	i;

	i = ft_strclen(*buffer, '\n');
	line = ft_strnew(0);
	if (!line)
		return (NULL);
	ft_add_to_line(fd, &line, buffer, i);
	if (!((*buffer)[0]))
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

int	free_return(char *buffer, int read_return)
{
	free(buffer);
	buffer = NULL;
	return (read_return);
}

/* Mallocate for buffer[fd] and read to it. */
int	get_next_line(const int fd, char **line)
{
	static char	*buffer[10240];
	int			read_return;

	if (fd < 0 || fd > 10240 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!buffer[fd])
		buffer[fd] = ft_strnew(BUFF_SIZE);
	if (!*(buffer[fd]))
	{
		if (!buffer[fd])
			return (-1);
		read_return = read(fd, buffer[fd], BUFF_SIZE);
		if (read_return > 0)
			*line = ft_create_line(fd, &(buffer[fd]));
		else
			return (free_return(buffer[fd], read_return));
		return (1);
	}
	else
	{
		*line = ft_create_line(fd, &(buffer[fd]));
		if (!line)
			return (-1);
		return (1);
	}
}
