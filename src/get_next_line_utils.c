/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:32:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/06/10 18:44:30 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (str)
	{
		j = 0;
		while (*(s1 + j))
			*(str + i++) = *(s1 + j++);
		j = 0;
		while (*(s2 + j))
			*(str + i++) = *(s2 + j++);
		str[i] = '\0';
	}
	free(s1);
	return (str);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen_gnl(s);
	if (start > l)
	{
		str = malloc(1);
		if (str)
		{
			str[0] = '\0';
			return (str);
		}
		return (NULL);
	}
	if (start + len > l)
		len = l - start;
	return (ft_strldup_gnl(s + start, len));
}

char	*ft_strldup_gnl(char *s1, size_t len)
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}
