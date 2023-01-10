/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:46:07 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/09 17:10:17 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	door_update(t_game *game)
{
	if (game->door.status)
	{
		if (game->door.frame < 32)
			game->door.frame++;
		else
			game->map.map[\
				(int)game->door.coord.y][(int)game->door.coord.x] = 'O';
	}
	else
	{
		if (game->door.frame > 0)
			game->door.frame--;
		game->map.map[\
			(int)game->door.coord.y][(int)game->door.coord.x] = 'D';
	}
}

void	door_toggle(t_game *game)
{
	int	x;
	int	y;

	x = (game->player.coord.x + cos(game->player.angle) * 100) / TILE_SIZE;
	y = (game->player.coord.y + sin(game->player.angle) * 100) / TILE_SIZE;
	if (x >= 0 && x < game->map.col && y >= 0 && y < game->map.row && \
		(game->map.map[y][x] == 'D' || game->map.map[y][x] == 'O'))
	{
		game->door.coord = (t_point){x, y};
		game->door.status ^= 1;
	}
}
