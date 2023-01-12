/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:25:57 by aho               #+#    #+#             */
/*   Updated: 2023/01/12 11:15:14 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include <fcntl.h>
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_arg_pars
{
	int		fd;
	char	*str;
}	t_arg_pars;

int				condition_map(char *str);
int				wall_inspect(char **tab, int line);
int				check_map(char *name);
char			**filling_tab(char *name);
int				check_name(char *name);
int				check_player(char *str);
int				parsing(char *name);
int				tab_row(char *name);
int				tab_col(char *name);
unsigned int	fc_color(char *name, char chr);
char			**path_texture(char *name);
void			ft_erase(char **array, int state);
int				nbr_player(char *name);
int				pars_bonus(char *name);
int				empty_fd(int fd);
void			pars_end(void);
void			p_error(char **tab);

#endif
