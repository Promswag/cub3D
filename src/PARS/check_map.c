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

void	p_error(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	nbr_of_line(int fd)
{
	char	*str;
	int		statut;
	int		line;

	line = 0;
	statut = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (statut == 1 && !(condition_map(str)))
			line++;
		else if (statut == 1 && condition_map(str))
		{
			free(str);
			return (-1);
		}
		else if (statut == 0 && !condition_map(str))
		{
			statut = 1;
			line++;
		}
		free(str);
		str = get_next_line(fd);
	}
	return (line);
}

void	fill_tab(char **tab, int fd)
{
	char	*str;
	int		x;

	x = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (!condition_map(str))
			tab[x++] = str;
		else
			free(str);
		str = get_next_line(fd);
	}
}

int	check_map(char *name)
{
	int		fd;
	char	**tab;
	int		i;
	int		result;

	fd = open(name, O_RDONLY);
	i = nbr_of_line(fd);
	if (i == -1 || i == 0)
		return (1);
	tab = ft_calloc((i + 1), sizeof(char *));
	close(fd);
	fd = open(name, O_RDONLY);
	fill_tab(tab, fd);
	close(fd);
	result = wall_inspect(tab, i);
	p_error(tab);
	if (result)
		return (1);
	else
		return (0);
}
