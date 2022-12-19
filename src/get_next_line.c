/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:32:05 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/06/10 18:39:04 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_is_a_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

static char	*gnl_buffer_handler(int fd, char *str)
{
	char	buffer[BUFFER_SIZE + 1];
	int		reading;

	reading = 1;
	if (!str)
		return (NULL);
	while (gnl_is_a_line(str) == -1 && reading)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading < 0)
		{
			free(str);
			return (NULL);
		}
		buffer[reading] = '\0';
		str = ft_strjoin_gnl(str, buffer);
	}
	return (str);
}

char	*gnl_retrieve_line(char **str)
{
	char	*line;
	char	*next_line;
	int		index;

	index = gnl_is_a_line(*str);
	if (index == -1)
	{
		line = *str;
		*str = NULL;
		return (line);
	}
	line = ft_substr_gnl(*str, 0, index + 1);
	next_line = ft_substr_gnl(*str, index + 1, ft_strlen_gnl(*str) - index - 1);
	free(*str);
	*str = next_line;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*tmp;

	if (fd < 0)
		return (NULL);
	if (!tmp)
	{
		tmp = malloc(sizeof(char));
		*tmp = '\0';
	}
	tmp = gnl_buffer_handler(fd, tmp);
	if (!tmp)
		return (NULL);
	if (!ft_strlen_gnl(tmp))
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	return (gnl_retrieve_line(&tmp));
}
