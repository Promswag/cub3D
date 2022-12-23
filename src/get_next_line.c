/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:32:05 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/22 13:44:34 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_isaline(char *s)
{
	int	i;

	i = -1;
	if (s)
		while (s[++i])
			if (s[i] == '\n')
				return (i + 1);
	return (-1);
}

static char	*gnl_line_handler(char **s)
{
	char	*line;
	char	*tmp;
	int		index;

	index = gnl_isaline(*s);
	if (index == -1)
	{
		line = *s;
		*s = NULL;
		return (line);
	}
	line = ft_strldup(*s, index);
	tmp = ft_strldup(*s + index, ft_strlen(*s + index));
	free(*s);
	*s = tmp;
	return (line);
}

static void	gnl_buffer_handler(int fd, char **s)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	int		reading;

	reading = 1;
	while (reading && gnl_isaline(*s) == -1)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading < 0)
			break ;
		buffer[reading] = 0;
		tmp = ft_strjoin(*s, buffer);
		free(*s);
		*s = tmp;
	}
}

char	*get_next_line(int fd)
{
	static char	*s;

	if (!s)
	{
		s = malloc(1);
		if (!s)
			return (NULL);
		*s = 0;
	}
	gnl_buffer_handler(fd, &s);
	if (!*s)
	{
		free(s);
		s = NULL;
		return (s);
	}
	return (gnl_line_handler(&s));
}
