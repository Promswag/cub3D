/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:40:42 by aho               #+#    #+#             */
/*   Updated: 2023/01/10 13:40:43 by aho              ###   ########.fr       */
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
	char	**tab;

	tab = ft_calloc(6, sizeof(char *));
	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "WE";
	tab[3] = "EA";
	tab[4] = "DO";
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
	redirection[2] = tab[2];
	redirection[0] = tab[3];
	redirection[4] = tab[4];
	return (redirection);
}

char	**path_texture(char *name)
{
	char	**direction;
	int		fd;
	char	*str;
	char	**tab;
	int		k;

	k = 0;
	direction = dir_init();
	fd = open(name, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		tab = ft_split(str, ' ');
		if (tab && condition_map(str) && condition_path(tab[0], direction[k]))
			direction[k++] = tab[1];
		free(str);
		if (k == 5)
			break ;
		str = get_next_line(fd);
	}
	close(fd);
	return (redirection_texture(direction));
}