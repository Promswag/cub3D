/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:20:55 by aho               #+#    #+#             */
/*   Updated: 2022/12/21 15:20:56 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

void	p_error(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	blank_line(int fd, int line)
{
	char	*str;
	int		statut;

	statut = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (statut && !(condition_map(str)))
			line++;
		else if (statut && condition_map(str))
		{
			free(str);
			return (empty_fd(fd));
		}
		else if (!statut && !condition_map(str))
		{
			statut++;
			line++;
		}
		free(str);
		str = get_next_line(fd);
	}
	empty_fd(fd);
	return (line);
}

int	check_map(char *name)
{
	char	**tab;
	int		result;
	int		fd;
	int		res;

	fd = open(name, O_RDONLY);
	res = blank_line(fd, 0);
	if (res == -1 || res == 0)
		return (1);
	tab = filling_tab(name);
	result = wall_inspect(tab, tab_row(name), tab_col(name));
	p_error(tab);
	if (result)
		return (1);
	else
		return (0);
}
