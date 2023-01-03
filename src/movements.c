/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:43:47 by gbaumgar          #+#    #+#             */
/*   Updated: 2023/01/03 15:38:44 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

t_point	move_point(t_game *game, float angle, float step)
{
	float	x;
	float	y;

	x = game->player.coord.x + cos(game->player.angle + angle) * step;
	y = game->player.coord.y + sin(game->player.angle + angle) * step;
	if ((int)x / TILE_SIZE >= 0 \
		&& (int)x / TILE_SIZE < \
		(int)ft_strlen(game->map.map[(int)game->player.coord.y / TILE_SIZE]) \
		&& game->map.map[\
		(int)game->player.coord.y / TILE_SIZE][(int)x / TILE_SIZE] != '1')
		;
	else
		x = game->player.coord.x;
	if ((int)y / TILE_SIZE >= 0 \
		&& (int)y / TILE_SIZE < game->map.row \
		&& game->map.map[\
		(int)y / TILE_SIZE][(int)game->player.coord.x / TILE_SIZE] != '1')
		;
	else
		y = game->player.coord.y;
	return ((t_point){x, y});
}

void	movements_handler(t_game *game)
{
	if (game->keys.w)
		game->player.coord = move_point(game, 0, 5);
	if (game->keys.s)
		game->player.coord = move_point(game, PI, 5);
	if (game->keys.a)
		game->player.angle = adjust_angle(game->player.angle - 2 * PI / 72);
	if (game->keys.d)
		game->player.angle = adjust_angle(game->player.angle + 2 * PI / 72);
	if (game->keys.q)
		game->player.coord = move_point(game, -(PI / 2), 5);
	if (game->keys.e)
		game->player.coord = move_point(game, PI / 2, 5);
}
