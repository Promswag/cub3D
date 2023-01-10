/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:25:57 by aho               #+#    #+#             */
/*   Updated: 2022/12/23 15:25:58 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H_PARSING_H
# define CUB3D_H_PARSING_H

# include <fcntl.h>
# include "get_next_line.h"
# include <stdio.h>

int		condition_map(char *str);
int		wall_inspect(char **tab, int line);
int		check_map(char *name);
char	**filling_tab(char *name);
int		check_name(char *name);
int		check_player(char *str);
int		parsing(char *name);
int		tab_row(char *name);
int		tab_col(char *name);

#endif
