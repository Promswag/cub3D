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
			result = 1;
	}
	p_error(texture);
	return (result);
}

int	check_texture(char *name)
{
	t_arg_pars	arg;
	int			stat;
	static char	*tab[] = {"NO", "SO", "WE", "EA", 0};
	int			i;

	i = 0;
	while (tab[i])
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
		i++;
	}
	return (i);
}
