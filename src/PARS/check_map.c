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

int	check_map(char *name)
{
	char	**tab;
	int		result;

	tab = filling_tab(name);
	result = wall_inspect(tab, tab_row(name), tab_col(name));
	p_error(tab);
	if (result)
		return (1);
	else
		return (0);
}
