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

int	condition_path(char *string, char *direction_brut)
{
	int	i;
	int	k;
	int	stat;

	k = 0;
	i = 0;
	stat = 0;
	while (string[i] == ' ')
		i++;
	while (direction_brut[k] && string[i])
	{
		if (direction_brut[k] == string[i])
			stat++;
		i++;
		k++;
	}
	if (stat == 2)
		return (1);
	return (0);
}

char	**dir_init(void)
{
	char	**retour;

	retour = ft_calloc(6, sizeof(char *));
	retour[0] = ft_strdup("NO");
	retour[1] = ft_strdup("SO");
	retour[2] = ft_strdup("WE");
	retour[3] = ft_strdup("EA");
	retour[4] = ft_strdup("DO");
	retour[5] = 0;
	return (retour);
}

char	**redirection_texture(char **tab, char **tofree)
{
	char	**redirection;
	int		i;
	int		k;

	i = -1;
	redirection = ft_calloc(6, sizeof(char *));
	while (tab[++i])
	{
		k = 0;
		while (tab[i][k] && tab[i][k] != '\n')
			k++;
		if (tab[i][k] == '\n')
			tab[i][k] = 0;
	}
	redirection[1] = ft_strdup(tab[0]);
	redirection[3] = ft_strdup(tab[1]);
	redirection[0] = ft_strdup(tab[2]);
	redirection[2] = ft_strdup(tab[3]);
	redirection[4] = ft_strdup(tab[4]);
	redirection[5] = 0;
	p_error(tab);
	p_error(tofree);
	return (redirection);
}

char	**path_texture(char *name)
{
	t_arg_pars	arg;
	char		**dir;
	char		**tab;
	char		**result;
	int			i;

	i = 0;
	result = ft_calloc(6, sizeof(char *));
	dir = dir_init();
	arg.fd = open(name, O_RDONLY);
	arg.str = get_next_line(arg.fd);
	while (arg.str && i < 5)
	{
		if (condition_path(arg.str, dir[i]))
		{
			tab = ft_split(arg.str, ' ');
			result[i] = ft_strdup(tab[1]);
			p_error(tab);
			i++;
		}
		free(arg.str);
		arg.str = get_next_line(arg.fd);
	}
	empty_fd(arg.fd);
	return (redirection_texture(result, dir));
}
