/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkatzenb <jkatzenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:42:30 by jkatzenb          #+#    #+#             */
/*   Updated: 2022/11/14 16:12:43 by jkatzenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

static char	*smth(int pos, char **buffer)
{
	char	*temp;
	char	*out;

	temp = 0;
	if (pos <= 0)
	{
		if (**buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		out = *buffer;
		*buffer = NULL;
		return (out);
	}
	temp = ft_substr(*buffer, pos, BUFFER_SIZE);
	out = *buffer;
	out[pos] = 0;
	*buffer = temp;
	return (out);
}

static char	*readthrough(int fd, char *readout, char **buffer)
{
	char		*temp;
	char		*nl;
	ssize_t		bytes;

	temp = NULL;
	nl = ft_strchr(*buffer, '\n');
	bytes = 0;
	while (nl == 0)
	{
		bytes = read(fd, readout, BUFFER_SIZE);
		if (bytes <= 0)
			return (smth(bytes, buffer));
		readout[bytes] = 0;
		temp = ft_strjoin(*buffer, readout);
		free(*buffer);
		*buffer = temp;
		nl = ft_strchr(*buffer, '\n');
	}
	return (smth(nl - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer[4069];
	char		*readout;
	char		*out;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	readout = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!readout)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = (char *)malloc(1 + sizeof(char));
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = 0;
	}
	out = readthrough(fd, readout, &buffer[fd]);
	free(readout);
	return (out);
}
