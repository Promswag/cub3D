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

char	**filling_tab3(char *tab, char *name, int chr, int line)
{
	char	**result;
	char	*str;
	int		save;
	int		cmp;
	int		fd;
	int		lg;


	save = 0;
	lg = 0;
	fd = open(name, O_RDONLY);
	str = get_next_line(fd);
	while (condition_map(str))
	{
		free(str);
		str = get_next_line(fd);
	}
	while (save < line)
	{
		cmp = 0;
		while (str[cmp])
		{
			if (str && (str[cmp] == '0' || str[cmp] == '1'))
				tab[lg] = str[cmp];
			else
				tab[lg] = '0';
			cmp++;
			lg++;
		}
		while (cmp < chr)
		{
			tab[lg] = '0';
			cmp++;
			lg++;
		}
		tab[lg++] = 'y';
		if (str)
		{
			free(str);
			str = get_next_line(fd);
		}
		save++;
	}
	result = ft_split(tab, 'y');
	return (result);
}

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
	free(str);
	close(fd);
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
	free(str);
	close(fd);
	return (col);
}

char	**filling_tab(char *name)
{
	int		col;
	int		row;
	char	*tab;

	col = tab_col(name);
	row = tab_row(name);
	tab = ft_calloc(((row + 1) * col), sizeof(char));
	return (filling_tab3(tab, name, col, row));
}