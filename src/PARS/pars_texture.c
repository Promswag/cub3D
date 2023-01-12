/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:40:42 by aho               #+#    #+#             */
/*   Updated: 2023/01/12 11:51:35 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	condition_path(char *dir, char *stc)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (stc[i])
	{
		if (dir[i] == stc[i])
			k++;
		i++;
	}
	if (k == 2)
		return (1);
	return (0);
}

char	**dir_init(void)
{
	static char	*tab[] = {"NO", "SO", "WE", "EA", "DO", 0};

	return (tab);
}

char	**redirection_texture(char **tab)
{
	char	**redirection;
	int		i;
	int		k;

	i = -1;
	redirection = ft_calloc(6, sizeof(char *));
	while (tab[++i])
	{
		k = 0;
		while (tab[i][k])
		{
			if (tab[i][k] == '\n')
			{
				tab[i][k] = 0;
				break ;
			}
			k++;
		}
	}
	redirection[1] = tab[0];
	redirection[3] = tab[1];
	redirection[0] = tab[2];
	redirection[2] = tab[3];
	redirection[4] = tab[4];
	return (redirection);
}

char	**path_texture(char *name)
{
	char	**dir;
	char	*str;
	char	**tab;
	int		k[2];

	k[0] = 0;
	dir = dir_init();
	k[1] = open(name, O_RDONLY);
	str = get_next_line(k[1]);
	while (str)
	{
		tab = ft_split(str, ' ');
		if (tab && condition_map(str) && condition_path(tab[0], dir[k[0]]))
			dir[k[0]++] = tab[1];
		else
			dir[4] = calloc(1, 1);
		free(str);
		free(tab[0]);
		free(tab);
		if (k[0] == 5)
			break ;
		str = get_next_line(k[1]);
	}
	empty_fd(k[1]);
	return (redirection_texture(dir));
}
