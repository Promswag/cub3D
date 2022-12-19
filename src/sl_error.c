/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:18:02 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/12/19 13:09:09 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		sl_args_handler(int argc, char **argv);
int		sl_error_handler(int error);

int	sl_args_handler(int argc, char **argv)
{
	int	l;

	if (argc == 1)
		return (sl_error_handler(1));
	if (argc > 2)
		return (sl_error_handler(2));
	l = ft_strlen(argv[1]);
	if (l < 4)
		return (sl_error_handler(3));
	if (!(argv[1][l - 4] == '.' && \
		argv[1][l - 3] == 'b' && \
		argv[1][l - 2] == 'e' && \
		argv[1][l - 1] == 'r'))
		return (sl_error_handler(3));
	return (0);
}

int	sl_error_handler(int error)
{
	ft_putstr_fd("Error\n", 2);
	if (error == 1)
		ft_putstr_fd("Missing map path.\n", 2);
	if (error == 2)
		ft_putstr_fd("Too many arguments.\n", 2);
	if (error == 3)
		ft_putstr_fd("Unauthorized file extension.\n", 2);
	if (error == 10)
		ft_putstr_fd("Read error.\n", 2);
	if (error == 11)
		ft_putstr_fd("Unauthorized map shape.\n", 2);
	if (error == 12)
		ft_putstr_fd("Map needs to be enclosed by walls.\n", 2);
	if (error == 13)
		ft_putstr_fd("Unauthorized characters.\n", 2);
	if (error == 14)
		ft_putstr_fd("Map needs 1 player spawn.\n", 2);
	if (error == 15)
		ft_putstr_fd("Map needs at least 1 collectible.\n", 2);
	if (error == 16)
		ft_putstr_fd("Map needs at least 1 exit.\n", 2);
	if (error == 17)
		ft_putstr_fd("Map needs a valid path.\n", 2);
	return (-1);
}
