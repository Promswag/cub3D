/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:49:15 by aho               #+#    #+#             */
/*   Updated: 2023/01/09 14:49:17 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	tab_row(char *name)
{
	int		fd;
	char	*str;
	int		row;

	row = 0;
	fd = open(name, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		if (!condition_map(str))
			row++;
		free(str);
		str = get_next_line(fd);
	}
	empty_fd(fd);
	return (row);
}

int	tab_col(char *name)
{
	char	*str;
	int		fd;
	int		i;
	int		col;

	col = 0;
	fd = open(name, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		i = 0;
		if (!condition_map(str))
		{
			while (str[i])
				i++;
		}
		if (i > col)
			col = i;
		free(str);
		str = get_next_line(fd);
	}
	empty_fd(fd);
	return (col);
}

char	**filling_tab3(char **tab, char *name)
{
	int		fd;
	char	*str;
	int		i;
	int		k;

	k = 0;
	fd = open(name, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		i = -1;
		while (!condition_map(str) && str[++i])
		{
			if (str[i] == '\n')
				tab[k++][i] = 0;
			else
				tab[k][i] = str[i];
		}
		free(str);
		str = get_next_line(fd);
	}
	empty_fd(fd);
	return (tab);
}

char	**filling_tab(char *name)
{
	int		col;
	int		row;
	int		i;
	char	**tab;

	i = 0;
	col = tab_col(name);
	row = tab_row(name);
	tab = ft_calloc((row + 1), (sizeof(char *)));
	while (i < row)
	{
		tab[i] = ft_calloc((col + 1), sizeof(char));
		i++;
	}
	return (filling_tab3(tab, name));
}
