/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:55:58 by aho               #+#    #+#             */
/*   Updated: 2023/01/11 12:56:00 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	nbr_player(char *name)
{
	t_arg_pars	arg;
	int			stat;
	int			i;

	stat = 0;
	arg.fd = open(name, O_RDONLY);
	arg.str = get_next_line(arg.fd);
	while (arg.str)
	{
		i = 0;
		while (!condition_map(arg.str) && arg.str[i])
		{
			if (arg.str[i] == 'E' || arg.str[i] == 'N'
				|| arg.str[i] == 'S' || arg.str[i] == 'W')
				stat++;
			i++;
		}
		free(arg.str);
		arg.str = get_next_line(arg.fd);
	}
	if (stat == 1)
		return (0);
	else
		return (1);
}

int	condition_map(char *str)
{
	int	x;
	int	blank;

	x = 0;
	blank = 1;
	while (str[x])
	{
		if (str[x] != '1' && str[x] != ' ' && str[x] != '0'
			&& str[x] != '\n' && str[x] != '\0'
			&& str[x] != 'N' && str[x] != 'E' && str[x] != 'S' && str[x] != 'W'
			&& str[x] != 'D' && str[x] != 'O')
			return (1);
		if (str[x] != ' ' && str[x] != '\n' && str[x] != '\0')
			blank = 0;
		x++;
	}
	if (blank == 1)
		return (1);
	return (0);
}

int	pars_bonus(char *name)
{
	t_arg_pars	arg;
	int			i;

	arg.fd = open(name, O_RDONLY);
	arg.str = get_next_line(arg.fd);
	while (arg.str)
	{
		i = 0;
		while (!condition_map(arg.str) && arg.str[i])
		{
			if (arg.str[i] == 'D' || arg.str[i] == 'O')
			{
				free(arg.str);
				return (1);
			}
			i++;
		}
		free(arg.str);
		arg.str = get_next_line(arg.fd);
	}
	return (0);
}
