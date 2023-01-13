/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_inspect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:34:40 by aho               #+#    #+#             */
/*   Updated: 2023/01/13 15:34:42 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	pars_texture_cmp(char *str, char *tofind)
{
	char	**texture;
	int		result;

	result = 0;
	texture = ft_split(str, ' ');
	if (ft_strnstr(texture[0], tofind, ft_strlen(tofind)))
	{
		if (texture[1] && texture[1][1])
		{
			while (texture[1 + result])
				result++;
		}
	}
	p_error(texture);
	if (result != 1)
		return (0);
	return (1);
}

int	check_texture(char *name)
{
	t_arg_pars	arg;
	int			stat;
	static char	*tab[] = {"NO", "SO", "WE", "EA", "F", "C", 0};
	int			i;

	i = -1;
	while (tab[++i])
	{
		stat = 0;
		arg.fd = open(name, O_RDONLY);
		arg.str = get_next_line(arg.fd);
		while (arg.str)
		{
			stat += pars_texture_cmp(arg.str, tab[i]);
			free(arg.str);
			arg.str = get_next_line(arg.fd);
		}
		empty_fd(arg.fd);
		if (stat != 1)
			break ;
	}
	return (i);
}

int	pars_line_pos(char *tofind, char *name)
{
	int		j;
	int		cmp;
	char	*str;
	int		fd;

	cmp = 0;
	fd = open(name, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		j = pars_texture_cmp(str, tofind);
		free(str);
		cmp++;
		if (j)
			break ;
		str = get_next_line(fd);
	}
	empty_fd(fd);
	return (cmp);
}

int	check_order(char *name)
{
	t_nbr_pars	nbr;
	static char	*tab[] = {"NO", "SO", "WE", "EA", "F", "C", 0};
	int			i;

	i = -1;
	nbr.save = 0;
	while (tab[++i])
	{
		nbr.cmp = pars_line_pos(tab[i], name);
		if (nbr.save > nbr.cmp)
			return (1);
		else
			nbr.save = nbr.cmp;
	}
	return (0);
}
