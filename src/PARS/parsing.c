/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:30 by aho               #+#    #+#             */
/*   Updated: 2023/01/11 16:20:34 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_name(char *name)
{
	char	*exe;
	int		i;
	int		j;

	exe = ".cub";
	i = 0;
	j = 0;
	while (name[i])
	{
		while (name[i] && exe[j] && name[i] == exe[j])
		{
			j++;
			i++;
		}
		if (exe[j] == '\0')
		{
			if (name[i] == '\0')
				return (0);
			else
				return (1);
		}
		j = 0;
		i++;
	}
	return (1);
}

int	check_dir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'E')
			return (E);
		else if (str[i] == 'N')
			return (N);
		else if (str[i] == 'W')
			return (W);
		else if (str[i] == 'S')
			return (S);
		i++;
	}
	return (-1);
}

int	check_player(char *name)
{
	char	*str;
	int		fd;
	int		result;

	result = -1;
	fd = open(name, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		if (!condition_map(str) && result == -1)
			result = check_dir(str);
		free(str);
		str = get_next_line(fd);
	}
	empty_fd(fd);
	return (result);
}

t_point	check_coor(char *name, t_point coor)
{
	t_arg_pars	index;
	int			i;

	index.fd = open(name, O_RDONLY);
	index.str = get_next_line(index.fd);
	while (index.str)
	{
		i = -1;
		if (!condition_map(index.str))
		{
			while (index.str[++i])
			{
				if (index.str[i] == 'E' || index.str[i] == 'N'
					|| index.str[i] == 'S' || index.str[i] == 'W')
					coor.x = i;
			}
			coor.y++;
		}
		free(index.str);
		if (coor.x != -1)
			break ;
		index.str = get_next_line(index.fd);
	}
	empty_fd(index.fd);
	return (coor);
}

int	parsing(char *name)
{
	if (check_map(name) || check_name(name)
		|| (check_player(name) == -1)
		|| nbr_player(name)
		|| check_texture(name) != 6
		|| check_order(name))
		return (1);
	return (0);
}
