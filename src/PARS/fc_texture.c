/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:10:26 by aho               #+#    #+#             */
/*   Updated: 2023/01/10 17:10:27 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_erase(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

unsigned int	pars_get_color(char *str)
{
	int				i;
	char			*split;
	int				k;
	char			**tab;
	unsigned int	color;

	split = ft_calloc(ft_strlen(str), sizeof(char));
	i = 0;
	k = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ',')
		{
			split[k] = str[i];
			k++;
		}
		i++;
	}
	tab = ft_split(split, ',');
	color = ((ft_atoi(tab[0]) << 24) + ((ft_atoi(tab[1])) << 16)
			+ (ft_atoi(tab[2]) << 8) + 255);
	free(split);
	ft_erase(tab);
	return (color);
}

int	condition_color(char *str, char chr)
{
	int	i;
	int	stat;

	stat = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			stat = 1;
		i++;
	}
	if (stat == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '\n'
			&& str[i] != ',' && str[i] != ' ' && str[i] != chr)
			stat = 0;
		i++;
	}
	return (stat);
}

unsigned int	fc_color(char *name, char chr)
{
	int				fd;
	char			*str;
	unsigned int	color;
	int				stat;

	color = 0x1C2E50FF;
	fd = open(name, O_RDONLY);
	str = get_next_line(fd);
	while (str && condition_map(str))
	{
		stat = 1;
		if (!condition_color(str, chr))
		{
			stat = 0;
		}
		if (stat == 1)
			color = pars_get_color(str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (color);
}
