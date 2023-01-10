/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:30 by aho               #+#    #+#             */
/*   Updated: 2022/12/29 13:04:31 by aho              ###   ########.fr       */
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
			return (0);
		else if (str[i] == 'N')
			return (1);
		else if (str[i] == 'W')
			return (2);
		else if (str[i] == 'S')
			return (3);
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
	close (fd);
	return (result);

}

int	parsing(char *name)
{
	if (check_map(name) || check_name(name)
		|| (check_player(name) == -1))
		return (1);
	return (0);
}
